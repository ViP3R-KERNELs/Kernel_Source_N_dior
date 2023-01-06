/*
 * Atmel maXTouch Touchscreen driver Plug in
 *
 * Copyright (C) 2013 Atmel Co.Ltd
 * Author: Pitter Liao <pitter.liao@atmel.com>
 * Copyright (C) 2015 XiaoMi, Inc.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */

/****************************************************************
	Pitter Liao add for macro for the global platform
	email:  pitter.liao@atmel.com
	mobile: 13244776877
-----------------------------------------------------------------*/
#define PLUG_VERSION 0x0047
/*----------------------------------------------------------------
0.47
1 add t6 message watchdog
0.46
1 alloc mem for store plugin parameter instead of gloable parameter
0.45
1 disable plugin in default

0.44
1 fix busg and store/show function
2 support internal threshold and algorithm in T100 workaround
3 support resume flag to sub plugin
4 fixed bug in dualx threshold

0.43
1 add t65 lpfilter control
0.42
1 deltet print information
2 impromve
0.41:
1 add invlaid value check
0.40
1 t65 support
0.39
1 fixed bugs which will crash when pluging not inited
0.38
1 t80 support
2 compatible bootloader mode
0.36
1 check inited tag at init()
0.35
1 add mxt_plugin_hook_reg_init
0.34
1 fixed bugs in deinit
0.33
1 fixed issue when plugin running but call plug_deinit
0.32
1 change check and calibration running indendent plug state
2 fix some bugs at _store()
0.31
1 modify print_trunk()
0.3
1 add t9/t100,t55 interface
0.2
1 add t61 support
2 modify t8 array to support step palm weaker
3 process state even when workaround is pause
0.11
1 version for simple workaround without debug message
0.1
1 first version support t37 and t72
*/

#include "plug.h"

static void plug_set_and_clr_flag(void * pl_dev, int mask_s, int mask_c)
{
	struct plug_interface *pl = pl_dev;
	struct plug_observer *obs = &pl->observer;

	set_and_clr_flag(mask_s, mask_c, &obs->flag);
}

void dec_dump_to_buffer(const void *buf, size_t num,
			char *linebuf, size_t linebuflen)
{
	int j, lx = 0;

	const s16 *ptr2 = buf;

	for (j = 0; j < num; j++)
		lx += scnprintf(linebuf + lx, linebuflen - lx,
				"%s%6d", j ? " " : "", *(ptr2 + j));

	linebuf[lx++] = '\0';
}

void print_dec_matrix(const char *level,const char *prefix_str,const void *buf,int x_size,int y_size)
{
	const s16 *ptr = buf;
	int i;
	unsigned char linebuf[7 * y_size + 1];

	for (i = 0; i < x_size; i ++) {
		dec_dump_to_buffer(ptr + i * y_size, y_size,
				   linebuf, sizeof(linebuf));
		printk("%s[mxt]%s\t%3d:  %s\n", level, prefix_str, i, linebuf);
	}
}

void print_matrix(const char *prefix,const s16 *buf,int x_size,int y_size)
{
	if (prefix)
		printk(KERN_INFO "[mxt]Print surface %s :\n",prefix);

	print_dec_matrix(KERN_INFO,"    ",buf,x_size,y_size);
}

void print_trunk(const u8 *data, int pos, int len)
{
#if defined(CONFIG_MXT_TRACK_TRUNK_DATA)
	u8 *buf = kmalloc(1024, GFP_KERNEL);
	if (buf == NULL)
		return;

	if (!len) {
		printk(KERN_INFO "[mxt] error len pos %d offset %d\n", pos, len);
		return;
	}

	if (len + 1 > sizeof(buf)) {
		printk(KERN_INFO "[mxt] too long string: pos %d offset %d\n", pos, len);
		len = sizeof(buf) - 1;
	}
	memcpy(buf, data + pos, len);
	buf[len] = '\0';
	printk(KERN_INFO "[mxt] %s \n",buf);
	kfree(buf);
#endif
}

static int config_matrix_init(struct mxt_config *dcfg, u8 matrix_xsize, u8 matrix_ysize)
{
	int i;

	//matrix retagle
	dcfg->m[MX].x0 = 0;
	dcfg->m[MX].y0 = 0;
	dcfg->m[MX].x1 = matrix_xsize - 1;
	dcfg->m[MX].y1 = matrix_ysize - 1;

	if (!dcfg->t15.xsize) {
		//aa absolute position
		dcfg->m[MX_POS].x0 = dcfg->t9_t100.x0;
		dcfg->m[MX_POS].y0 = dcfg->t9_t100.y0;
		dcfg->m[MX_POS].x1 = 0;
		dcfg->m[MX_POS].y1 = 0;

		//aa relative retangle
		dcfg->m[MX_AA].x0 = 0;
		dcfg->m[MX_AA].y0 = 0;
		dcfg->m[MX_AA].x1 = dcfg->t9_t100.xsize - 1;
		dcfg->m[MX_AA].y1 = dcfg->t9_t100.ysize - 1;

		//touch aa relative retangle
		dcfg->m[MX_T].x0 = 0;
		dcfg->m[MX_T].y0 = 0;
		dcfg->m[MX_T].x1 = dcfg->t9_t100.xsize - 1;
		dcfg->m[MX_T].y1 = dcfg->t9_t100.ysize - 1;

		dcfg->m[MX_K].x0 = -1;
		dcfg->m[MX_K].y0 = -1;
		dcfg->m[MX_K].x1 = -1;
		dcfg->m[MX_K].y1 = -1;
	} else {
		//aa absolute position
		dcfg->m[MX_POS].x0 = min_t(int, dcfg->t15.x0, dcfg->t9_t100.x0);
		dcfg->m[MX_POS].y0 = min_t(int, dcfg->t15.y0, dcfg->t9_t100.y0);
		dcfg->m[MX_POS].x1 = 0;
		dcfg->m[MX_POS].y1 = 0;

		//aa relative retangle
		dcfg->m[MX_AA].x0 = 0;
		dcfg->m[MX_AA].y0 = 0;
		dcfg->m[MX_AA].x1 = dcfg->t9_t100.xsize - 1;
		if (dcfg->t15.x0 < dcfg->t9_t100.x0 || dcfg->t15.x0 > dcfg->t9_t100.x0 + dcfg->t9_t100.xsize - 1)
			dcfg->m[MX_AA].x1 += dcfg->t15.xsize;
		dcfg->m[MX_AA].y1 = dcfg->t9_t100.ysize - 1;
		if (dcfg->t15.y0 < dcfg->t9_t100.y0 || dcfg->t15.y0 > dcfg->t9_t100.y0 + dcfg->t9_t100.ysize - 1)
			dcfg->m[MX_AA].y1 += dcfg->t15.ysize;

		//touch aa relative retangle
		if (dcfg->t15.x0 < dcfg->t9_t100.x0){
			dcfg->m[MX_T].x0 = dcfg->t9_t100.x0 - dcfg->t15.x0;
		} else {
			dcfg->m[MX_T].x0 = 0;
		}

		if (dcfg->t15.y0 < dcfg->t9_t100.y0){
			dcfg->m[MX_T].y0 = dcfg->t9_t100.y0 - dcfg->t15.y0;
		} else {
			dcfg->m[MX_T].y0 = 0;
		}
		dcfg->m[MX_T].x1 = dcfg->m[MX_T].x0 + dcfg->t9_t100.xsize - 1;
		dcfg->m[MX_T].y1 = dcfg->m[MX_T].y0 + dcfg->t9_t100.ysize - 1;

		//key aa relative retangle
		if (dcfg->t15.x0 < dcfg->t9_t100.x0) {
			dcfg->m[MX_K].x0 = 0;
		} else {
			dcfg->m[MX_K].x0 = dcfg->t15.x0 - dcfg->t9_t100.x0;
		}

		if (dcfg->t15.y0 < dcfg->t9_t100.y0) {
			dcfg->m[MX_K].y0 = 0;
		} else {
			dcfg->m[MX_K].y0 = dcfg->t15.y0 - dcfg->t9_t100.y0;
		}
		dcfg->m[MX_K].x1 = dcfg->m[MX_K].x0 + dcfg->t15.xsize - 1;
		dcfg->m[MX_K].y1 = dcfg->m[MX_K].y0 + dcfg->t15.ysize - 1;
	}

	for (i = 0; i < MX_SUM; i++) {
		printk(KERN_INFO "[mxt]dcfg: Matrix %d (%d,%d)~(%d,%d)\n",
				i,
				dcfg->m[i].x0,
				dcfg->m[i].y0,
				dcfg->m[i].x1,
				dcfg->m[i].y1);
	}

	return 0;
}

static int mxt_t6_command(struct mxt_data *data, u16 cmd_offset,
			u8 value, bool wait)
{
	u16 reg;
	u8 command_register;
	int timeout_counter = 0;
	int ret = 0;

	reg = data->T6_address + cmd_offset;

	reg = mxt_write_reg(data->client, reg, value);
	if (ret)
		return ret;
	if (!wait)
		return 0;
	do {
		msleep(20);
		ret = __mxt_read_reg(data->client, reg, 1, &command_register);
		if (ret)
			return ret;
	} while ((command_register != 0) && (timeout_counter++ <= 100));

	if (timeout_counter > 100) {
		dev_err(&data->client->dev, "Command failed!\n");
		return -EIO;
	}

	return 0;
}

static int mxt_diagnostic_command(struct mxt_data *data, u8 cmd, u8 page, u8 index, u8 num, void * buf, int no_wait)
{
	u16 reg;
	s8 command_register[2];
	s8 current_page,page_cmd;
	int ret;
#define MXT_DIAG_TIME_COUNT_MAX 5
#define MXT_PAGE_TIME_COUNT_MAX 5
#define MXT_TIMEOUT_COUNT_MAX 5
	int timeout_counter,retry;

	long unsigned int time_start = jiffies;

	reg = data->T37_address;
	ret = __mxt_read_reg(data->client, reg, sizeof(command_register), &command_register[0]);
	if (ret) {
		dev_err(&data->client->dev, "T37 read offset 0 failed %d!\n",ret);
		return -EIO;
	}
	if (command_register[0] != cmd) {
		ret = mxt_t6_command(data, MXT_COMMAND_DIAGNOSTIC, cmd, 0);
		if (ret){
			dev_err(&data->client->dev, "T6 Command DIAGNOSTIC cmd 0x%x failed %d!\n",cmd,ret);
			return -EIO;
		}
		current_page = 0;
	} else {
		current_page = command_register[1];
		if (abs((s8)current_page - (s8)page) > (s8)page) {// far away with dis page
			ret = mxt_t6_command(data, MXT_COMMAND_DIAGNOSTIC, cmd, 0);
			if  (ret) {
				dev_err(&data->client->dev, "T6 Command DIAGNOSTIC cmd 0x%x failed %d!\n",cmd,ret);
				return -EIO;
			}
			current_page = 0;
		}
	}

	//wait command
	timeout_counter = 0;
	do {
		reg = data->T37_address;
		ret = __mxt_read_reg(data->client, reg, sizeof(command_register), &command_register[0]);
		if (ret) {
			dev_err(&data->client->dev, "T37 read offset 0 failed %d!\n",ret);
			return -EIO;
		}

		if (command_register[0] == cmd)
			break;

		if (no_wait)
			return -EAGAIN;

		msleep(1);
	} while (timeout_counter++ <= MXT_DIAG_TIME_COUNT_MAX);

	if (timeout_counter > MXT_DIAG_TIME_COUNT_MAX) {
		dev_err(&data->client->dev,
			"T37 wait cmd %d page %d current page %d timeout(%d %d) ##1\n",
			cmd,page,current_page,command_register[0],command_register[1]);
		return -EBUSY;
	}

	//current_page = command_register[1];
	retry = 0;
	while (current_page != page) {

		if (current_page > page) {
			page_cmd = MXT_T6_DEBUG_PAGEDOWN;
			current_page--;
		} else {
			page_cmd = MXT_T6_DEBUG_PAGEUP;
			current_page++;
		}

		time_start = jiffies;

		ret = mxt_t6_command(data, MXT_COMMAND_DIAGNOSTIC,page_cmd, 0);
		if (ret) {
			dev_err(&data->client->dev,
			"T6 Command DIAGNOSTIC page %d to page %d failed %d!\n",current_page,page,ret);
			return -EIO;
		}

		if (no_wait)
			return -EAGAIN;

		//fix me: here need wait every cycle?
		timeout_counter = 0;
		do {
			reg = data->T37_address;
			ret = __mxt_read_reg(data->client, reg,
						sizeof(command_register), &command_register[0]);
			if (ret) {
				dev_err(&data->client->dev, "T37 read offset 0 failed %d!\n",ret);
				return -EIO;
			}
			if (command_register[0] != cmd) {
				break;
			}
			if (current_page == command_register[1])
				break;

			msleep(1);
		} while (timeout_counter++ <= MXT_DIAG_TIME_COUNT_MAX);

		if (timeout_counter > MXT_DIAG_TIME_COUNT_MAX) {
			if (retry++ > MXT_TIMEOUT_COUNT_MAX) {
				dev_err(&data->client->dev,
					"T37 wait cmd %d page %d current page %d timeout(%d %d) page_cmd %d retry %d ##2\n",
					cmd,page,current_page,command_register[0],command_register[1],page_cmd,retry);
				return -EBUSY;
			}
		}
		if (command_register[0] != cmd) {
			dev_err(&data->client->dev,
				"T37 wait cmd %d page %d current page %d timeout(%d %d) ##3\n",
				cmd,page,current_page,command_register[0],command_register[1]);
			return -EBUSY;

		}
		current_page = command_register[1];

		dev_dbg(&data->client->dev, "T37 page command ticks %lu\n",jiffies - time_start);
	}

	if (buf) {
		ret = __mxt_read_reg(data->client, data->T37_address + (index + 1) * sizeof(s16),//add offset 1
				num * sizeof(s16), buf);
		if (ret) {
			dev_err(&data->client->dev,
				"Failed to read T37 val at page %d.%d (%d)\n", page, index, ret);
			return -EIO;
		}

		//check the command again
		ret = __mxt_read_reg(data->client, reg, sizeof(command_register), &command_register[0]);
		if (ret) {
			dev_err(&data->client->dev, "T37 read offset 0 failed %d!\n",ret);
			return -EIO;
		} 

		if (command_register[0] != cmd || command_register[1] != page) {
			dev_err(&data->client->dev, "T37 page changed (%d,%d) -> (%d,%d)\n",
					cmd,
					page,
					command_register[0],
					command_register[1]);
			return -EIO;
		}
	}

	return 0;
}

int mxt_diagnostic_reset_page(void *dev_id, u8 cmd, int no_wait)
{
	struct mxt_data *data = dev_id;
	u16 reg;
	s8 command_register[2];
	int ret;
#define MXT_DIAG_TIME_COUNT_MAX 5
	int timeout_counter;

	ret = mxt_t6_command(data, MXT_COMMAND_DIAGNOSTIC, cmd, 0);
	if (ret) {
		dev_err(&data->client->dev,
			"T6 Command DIAGNOSTIC cmd 0x%x failed %d!\n", cmd, ret);
			return -EIO;
	}

	//wait command
	timeout_counter = 0;
	do {
		reg = data->T37_address;
		ret = __mxt_read_reg(data->client, reg, sizeof(command_register), &command_register[0]);
		if (ret) {
			dev_err(&data->client->dev, "T37 reset offset 0 failed %d!\n",ret);
			return -EIO;
		}

		if (command_register[0] == cmd)
			break;

		if (no_wait)
			return -EAGAIN;

		msleep(1);
	} while (timeout_counter++ <= MXT_DIAG_TIME_COUNT_MAX);

	if (timeout_counter > MXT_DIAG_TIME_COUNT_MAX) {
		dev_err(&data->client->dev, "T37 reset cmd %d timeout(%d %d) ##1\n",
			cmd, command_register[0], command_register[1]);
		return -EBUSY;
	}

	return 0;
}


int mxt_get_current_page_info(void * dev_id, s8 command_register[2])
{
	struct mxt_data *data = dev_id;
	u16 reg;
	int ret;

	reg = data->T37_address;
	ret = __mxt_read_reg(data->client, reg, sizeof(command_register), &command_register[0]);
	if (ret) {
		dev_err(&data->client->dev, "T37 read offset 0 failed!\n");
		return ret;
	}

	return 0;
}

int mxt_surface_page_aquire(void *dev_id, s16 *buf,u8 cmd, const struct rect *surface, struct rect *pst,int y_offset,int *out_pos,int no_wait)
{
	struct mxt_data *data = dev_id;
	struct plug_interface *pl = &data->plug_in;
	const struct mxt_config *dcfg = &pl->init_cfg;
	struct device *dev = &data->client->dev;
	int y_matrix_size;
	int y_size,y_size_left,pos,page,next_page,idx;
	int valid_size;
	int retry = 3;
	int i;

	s16 page_buf[MXT_PAGE_SIZE];

	int ret = -EFAULT;

	y_matrix_size = dcfg->m[MX].y1 - dcfg->m[MX].y0 + 1;

	y_size = surface->y1 - surface->y0 + 1;
	y_size_left = y_size - y_offset;
	pos = pst->x0 * y_matrix_size + pst->y0 + y_offset;
	next_page = page = pos / MXT_PAGE_SIZE;
	idx = pos % MXT_PAGE_SIZE;
	valid_size = 0;

	dev_dbg2(dev,"mxt surface page aquire %d (%d,%d)-(%d,%d) pos %d offset %d left %d\n",
			cmd,pst->x0,pst->y0,pst->x1,pst->y1,pos,y_offset,y_size_left);

	for (i = pst->x0; i <= pst->x1;) {//readout one y line data each time

		//at current y line end position,page and idx
		pos = i * y_matrix_size + pst->y1;
		if ((pos / MXT_PAGE_SIZE) != page) {//read to the end of this page
			valid_size = MXT_PAGE_SIZE - idx;
		} else {
			valid_size = (pos % MXT_PAGE_SIZE) - idx + 1;
		}

		dev_dbg2(dev,"mxt surface page aquire page %d idx %d size %d left %d\n",
				page,idx,valid_size,y_size_left);

		if (i == pst->x0) {
			ret = mxt_diagnostic_command(data, cmd, page, idx, valid_size, page_buf, no_wait);
			if (ret) {
				dev_dbg2(dev, "Failed to get page %d idx %d size %d (%d)\n", page, idx, valid_size, ret);
				if (no_wait)
					break;
				else if (ret == -EBUSY && --retry)
					continue;
			}
		} else {
			ret = __mxt_read_reg(data->client, data->T37_address + (idx + 1) * sizeof(s16),  //add offset 1
					valid_size * sizeof(s16), page_buf);
			if (ret) {
				dev_err(&data->client->dev, "Failed to read T37 val at page %d.%d (%d)\n", page, idx, ret);
				break;
			}
		}

		memcpy(buf,page_buf,valid_size*sizeof(s16));
		buf += valid_size;

		y_size_left -= valid_size;
		if (y_size_left)
			break;
		else {
			pos = (i + 1) * y_matrix_size + pst->y0;
			next_page = pos / MXT_PAGE_SIZE;
			if (page != next_page)
				break;

			y_size_left = y_size;
			page = next_page;
			idx = pos % MXT_PAGE_SIZE;
		}

		i++;
	}

	if (ret == 0) {
		if (y_size_left || (page != next_page))
			mxt_t6_command(data, MXT_COMMAND_DIAGNOSTIC,MXT_T6_DEBUG_PAGEDOWN, 0);//perpare next page data
	}
	pos = i * y_size + (y_size - y_size_left);

	if (y_size_left) {
		pst->x1 = i;
		pst->y1 = pst->y0 + y_size - y_size_left;
	} else {
		pst->x1 = i + 1;
		pst->y1 = pst->y0;
	}

	dev_dbg2(dev,"mxt surface page end at(%d,%d) pos %d ret %d\n",
			pst->x1,pst->y1,pos,ret);

	if (out_pos)
		*out_pos = pos;

	return ret;
}

static int mxt_get_init_config_t8(struct mxt_data *data,struct t8_config *cfg)
{
	struct device *dev = &data->client->dev;
	int error;

	error = __mxt_read_reg(data->client, data->T8_address + MXT_T8_ATCHCALST,
			1, &cfg->atchcalst);
	if (error) {
		dev_err(dev, "Failed to read T8 ATCHCALST %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T8_address + MXT_T8_ATCHCALSTHR,
			1, &cfg->atchcalsthr);
	if (error) {
		dev_err(dev, "Failed to read T8 ATCHCALSTHR %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T8_address + MXT_T8_ATCHFRCCALTHR,
			1, &cfg->atchfrccalthr);
	if (error) {
		dev_err(dev, "Failed to read T8 ATCHFRCCALTHR %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T8_address + MXT_T8_ATCHFRCCALRATIO,
			1, &cfg->atchfrccalratio);
	if (error) {
		dev_err(dev, "Failed to read T8 ATCHFRCCALRATIO %d\n", error);
		return -EIO;
	}
	return 0;
}

static int mxt_get_init_config_t9(struct mxt_data *data,struct t9_t100_config *cfg)
{
	struct device *dev = &data->client->dev;
	int error;

	error = __mxt_read_reg(data->client, data->T9_address + MXT_T9_XORIGN,
			1, &cfg->x0);
	if (error) {
		dev_err(dev, "Failed to read T9 XORIGN %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T9_address + MXT_T9_YORIGN,
			1, &cfg->y0);
	if (error) {
		dev_err(dev, "Failed to read T9 YORIGN %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T9_address + MXT_T9_XSIZE,
			1, &cfg->xsize);
	if (error) {
		dev_err(dev, "Failed to read T9 XSIZE %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T9_address + MXT_T9_YSIZE,
			1, &cfg->ysize);
	if (error) {
		dev_err(dev, "Failed to read T9 YSIZE %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T9_address + MXT_T9_TCHHR,
			1, &cfg->threshold);
	if (error) {
		dev_err(dev, "Failed to read T9 TCHHR %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T9_address + MXT_T9_TCHHYST,
			1, &cfg->hysterisis);
	if (error) {
		dev_err(dev, "Failed to read T9 TCHHYST %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T9_address + MXT_T9_NUMTOUCH,
			1, &cfg->num_touch);
	if (error) {
		dev_err(dev, "Failed to read T9 NUMTOUCH %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T9_address + MXT_T9_MRGTHR,
			1, &cfg->merge_threshold);
	if (error) {
		dev_err(dev, "Failed to read T9 MRGTHR %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T9_address + MXT_T9_MRGHYST,
			1, &cfg->merge_hysterisis);
	if (error) {
		dev_err(dev, "Failed to read T9 MRGHYST %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T9_address + MXT_T9_DUALX_THLD,
			1, &cfg->dualx_threshold);
	if (error) {
		dev_err(dev, "Failed to read T9 DUALX_THLD %d\n", error);
		return -EIO;
	}

	cfg->internal_threshold = cfg->threshold >> 1;
	cfg->internal_hysterisis = cfg->hysterisis;

	return 0;
}

static int mxt_get_init_config_t100(struct mxt_data *data,struct t9_t100_config *cfg)
{
	struct device *dev = &data->client->dev;
	u8 val;
	int error;

	error = __mxt_read_reg(data->client, data->T100_address + MXT_T100_XORIGN,
			1, &cfg->x0);
	if (error) {
		dev_err(dev, "Failed to read T100 XORIGN %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T100_address + MXT_T100_YORIGN,
			1, &cfg->y0);
	if (error) {
		dev_err(dev, "Failed to read T100 YORIGN %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T100_address + MXT_T100_XSIZE,
			1, &cfg->xsize);
	if (error) {
		dev_err(dev, "Failed to read T100 XSIZE %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T100_address + MXT_T100_YSIZE,
			1, &cfg->ysize);
	if (error) {
		dev_err(dev, "Failed to read T100 YSIZE %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T100_address + MXT_T100_TCHHR,
			1, &cfg->threshold);
	if (error) {
		dev_err(dev, "Failed to read T100 TCHHR %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T100_address + MXT_T100_TCHHYST,
			1, &cfg->hysterisis);
	if (error) {
		dev_err(dev, "Failed to read T100 TCHHYST %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T100_address + MXT_T100_INTTHR,
		1, &cfg->internal_threshold);
	if (error) {
		dev_err(dev, "Failed to read T100 INTTHR %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T100_address + MXT_T100_INTTHRHYST,
		1, &cfg->internal_hysterisis);
	if (error) {
		dev_err(dev, "Failed to read T100 INTTHRHYST %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T100_address + MXT_T100_NUMTOUCH,
			1, &cfg->num_touch);
	if (error) {
		dev_err(dev, "Failed to read T100 NUMTOUCH %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T100_address + MXT_T100_MRGTHR,
			1, &cfg->merge_threshold);
	if (error) {
		dev_err(dev, "Failed to read T100 MRGTHR %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T100_address + MXT_T100_MRGHYST,
			1, &cfg->merge_hysterisis);
	if (error) {
		dev_err(dev, "Failed to read T100 MRGHYST %d\n", error);
		return -EIO;
	}
	error = __mxt_read_reg(data->client, data->T100_address + MXT_T100_DXTHRSF,
			1, &val);
	if (error) {
		dev_err(dev, "Failed to read T100 DXTHRSF %d\n", error);
		return -EIO;
	}
	if (val == 0)
		val = 128;
	cfg->dualx_threshold = ((u32)cfg->threshold * val) >> 7;

	if (cfg->xsize == 0)
		cfg->xsize = 1;
	if (cfg->ysize == 0)
		cfg->ysize = 1;
	return 0;
}


static int mxt_get_init_config_t15(struct mxt_data *data,struct t15_config *cfg)
{
	struct device *dev = &data->client->dev;
	int error;
	u8 val;

	error = __mxt_read_reg(data->client, data->T15_address,
			1, &val);
	if (error) {
		dev_err(dev, "Failed to read T15 EN %d\n", error);
		return -EIO;
	}

	if (val & 0x1) { //enable
		error = __mxt_read_reg(data->client, data->T15_address + MXT_T15_XORIGN,
				1, &cfg->x0);
		if (error) {
			dev_err(dev, "Failed to read T15 XORIGN %d\n", error);
			return -EIO;
		}
		error = __mxt_read_reg(data->client, data->T15_address + MXT_T15_YORIGN,
				1, &cfg->y0);
		if (error) {
			dev_err(dev, "Failed to read T15 YORIGN %d\n", error);
			return -EIO;
		}
		error = __mxt_read_reg(data->client, data->T15_address + MXT_T15_XSIZE,
				1, &cfg->xsize);
		if (error) {
			dev_err(dev, "Failed to read T15 XSIZE %d\n", error);
			return -EIO;
		}
		error = __mxt_read_reg(data->client, data->T15_address + MXT_T15_YSIZE,
				1, &cfg->ysize);
		if (error) {
			dev_err(dev, "Failed to read T15 YSIZE %d\n", error);
			return -EIO;
		}
		error = __mxt_read_reg(data->client, data->T15_address + MXT_T15_TCHHR,
				1, &cfg->threshold);
		if (error) {
			dev_err(dev, "Failed to read T15 TCHHR %d\n", error);
			return -EIO;
		}
	} else {
		memset(cfg,0,sizeof(*cfg));
	}

	return 0;
}

static int mxt_get_init_config_t38(struct mxt_data *data,struct t38_config *cfg)
{
	struct device *dev = &data->client->dev;
	int error;

	error = __mxt_read_reg(data->client, data->T38_address,
			sizeof(*cfg), cfg);
	if (error) {
		dev_err(dev, "Failed to read T38 %d\n", error);
		return -EIO;
	}

	return 0;
}

static int mxt_get_init_config_t40(struct mxt_data *data,struct t40_config *cfg)
{
	struct device *dev = &data->client->dev;
	int error;

	error = __mxt_read_reg(data->client, data->T40_address,
			sizeof(*cfg), cfg);
	if (error) {
		dev_err(dev, "Failed to read T40 %d\n", error);
		return -EIO;
	}

	return 0;
}

static int mxt_get_init_config_t55(struct mxt_data *data,struct t55_config *cfg)
{
	struct device *dev = &data->client->dev;
	int error;

	error = __mxt_read_reg(data->client, data->T55_address,
			sizeof(*cfg), cfg);
	if (error) {
		dev_err(dev, "Failed to read T55 %d\n", error);
		return -EIO;
	}

	return 0;
}

static int mxt_get_init_config_t61(struct mxt_data *data,struct t61_config *cfg, int instance)
{
	struct device *dev = &data->client->dev;
	int error;

	error = __mxt_read_reg(data->client, data->T61_address,
			sizeof(*cfg) * instance, cfg);
	if (error) {
		dev_err(dev, "Failed to read T61 %d\n", error);
		return -EIO;
	}

	return 0;
}

static int mxt_get_init_config_t65(struct mxt_data *data,struct t65_config *cfg)
{
	struct device *dev = &data->client->dev;
	int error;

	error = __mxt_read_reg(data->client, data->T65_address,
			sizeof(*cfg), cfg);
	if (error) {
		dev_err(dev, "Failed to read T65 %d\n", error);
		return -EIO;
	}

	return 0;
}

static int mxt_get_init_config_t80(struct mxt_data *data,struct t80_config *cfg)
{
	struct device *dev = &data->client->dev;
	int error;

	error = __mxt_read_reg(data->client, data->T80_address,
			sizeof(*cfg), cfg);
	if (error) {
		dev_err(dev, "Failed to read T80 %d\n", error);
		return -EIO;
	}

	return 0;
}

static int mxt_set_t6_cal(void *pl_dev)
{
	struct plug_interface *pl = pl_dev;
	struct mxt_data *data = pl->dev;

	return mxt_t6_command(data, MXT_COMMAND_CALIBRATE, 1, false);
}

static int mxt_set_obj_t8(struct mxt_data *data,struct t8_config *cfg,unsigned long unset)
{
	struct device *dev = &data->client->dev;

	dev_info(dev, "mxt set t8 %d %d %d %d\n",
			cfg->atchcalst,
			cfg->atchcalsthr,
			cfg->atchfrccalthr,
			cfg->atchfrccalratio);

	if (!test_bit(MXT_T8_MASK_ATCHCALST,&unset))
		mxt_write_object(data,MXT_GEN_ACQUISITIONCONFIG_T8,MXT_T8_ATCHCALST,cfg->atchcalst);
	if (!test_bit(MXT_T8_MASK_ATCHCALSTHR,&unset))
		mxt_write_object(data,MXT_GEN_ACQUISITIONCONFIG_T8,MXT_T8_ATCHCALSTHR,cfg->atchcalsthr);
	if (!test_bit(MXT_T8_MASK_ATCHFRCCALTHR,&unset))
		mxt_write_object(data,MXT_GEN_ACQUISITIONCONFIG_T8,MXT_T8_ATCHFRCCALTHR,cfg->atchfrccalthr);
	if (!test_bit(MXT_T8_MASK_ATCHFRCCALRATIO,&unset))
		mxt_write_object(data,MXT_GEN_ACQUISITIONCONFIG_T8,MXT_T8_ATCHFRCCALRATIO,cfg->atchfrccalratio);

	return 0;
}

static int mxt_set_t8_cfg(void *pl_dev,int state,unsigned long unset)
{
	struct plug_interface *pl = pl_dev;
	struct mxt_data *data = pl->dev;
	struct device *dev = &data->client->dev;
	struct plug_config *cfg = &pl->config;
	struct t8_config *t8_cfg;

	if (state >= cfg->num_t8_config) {
		dev_err(dev, "mxt_set_t8_cfg: invalid t8 state %d\n",state);
		return -EINVAL;
	} else {
		t8_cfg = &cfg->t8_cfg[state];
		return mxt_set_obj_t8(data,t8_cfg,unset);
	}
}

static int mxt_set_obj_t9(struct mxt_data *data,struct t9_t100_config *cfg,unsigned long unset)
{
	struct device *dev = &data->client->dev;
	struct input_dev *input_dev;
	u16 reg;
	u8 val;
	int i;

	dev_info(dev, "mxt set t9 %d %d %d %d %d\n",
			cfg->threshold,
			cfg->hysterisis,
			cfg->merge_threshold,
			cfg->merge_hysterisis,
			cfg->num_touch);

	if (!test_bit(MXT_T9_T100_MASK_TCHHR,&unset))
		mxt_write_object(data,MXT_TOUCH_MULTITOUCHSCREEN_T9,MXT_T9_TCHHR,cfg->threshold);
	if (!test_bit(MXT_T9_T100_MASK_TCHHYST,&unset))
		mxt_write_object(data,MXT_TOUCH_MULTITOUCHSCREEN_T9,MXT_T9_TCHHYST,cfg->hysterisis);
	if (!test_bit(MXT_T9_T100_MASK_MRGTHR,&unset))
		mxt_write_object(data,MXT_TOUCH_MULTITOUCHSCREEN_T9,MXT_T9_MRGTHR,cfg->merge_threshold);
	if (!test_bit(MXT_T9_T100_MASK_MRGHYST,&unset))
		mxt_write_object(data,MXT_TOUCH_MULTITOUCHSCREEN_T9,MXT_T9_MRGHYST,cfg->merge_hysterisis);
	if (!test_bit(MXT_T9_T100_MASK_N_TOUCH,&unset)){
		reg = data->T9_address + MXT_T9_NUMTOUCH;
		if (__mxt_read_reg(data->client, reg, 1, &val) == 0) {
			__mxt_write_reg(data->client,reg,1,&cfg->num_touch);

			if (val > cfg->num_touch) {
				input_dev = data->input_dev;
				if (input_dev) {
					for (i = cfg->num_touch; i < val; i++) {
						input_mt_slot(input_dev, i);
						input_mt_report_slot_state(input_dev, MT_TOOL_FINGER, 0);
					}
					mxt_input_sync(data);
				}
			}
		}
	}
	return 0;
}

static int mxt_set_obj_t100(struct mxt_data *data,struct t9_t100_config *cfg,unsigned long unset)
{
	struct device *dev = &data->client->dev;
	struct input_dev *input_dev;
	u16 reg;
	u8 val;
	int i;

	dev_info(dev, "mxt set t100 %d %d %d %d %d\n",
			cfg->threshold,
			cfg->hysterisis,
			cfg->merge_threshold,
			cfg->merge_hysterisis,
			cfg->num_touch);

	if (!test_bit(MXT_T9_T100_MASK_TCHHR,&unset))
		mxt_write_object(data,MXT_TOUCH_MULTITOUCHSCREEN_T100,MXT_T100_TCHHR,cfg->threshold);
	if (!test_bit(MXT_T9_T100_MASK_TCHHYST,&unset))
		mxt_write_object(data,MXT_TOUCH_MULTITOUCHSCREEN_T100,MXT_T100_TCHHYST,cfg->hysterisis);
	if (!test_bit(MXT_T9_T100_MASK_MRGTHR,&unset))
		mxt_write_object(data,MXT_TOUCH_MULTITOUCHSCREEN_T100,MXT_T100_MRGTHR,cfg->merge_threshold);
	if (!test_bit(MXT_T9_T100_MASK_MRGHYST,&unset))
		mxt_write_object(data,MXT_TOUCH_MULTITOUCHSCREEN_T100,MXT_T100_MRGHYST,cfg->merge_hysterisis);
	if (!test_bit(MXT_T9_T100_MASK_N_TOUCH,&unset)){
		reg = data->T100_address + MXT_T100_NUMTOUCH;
		if (__mxt_read_reg(data->client, reg, 1, &val) == 0) {
			__mxt_write_reg(data->client,reg,1,&cfg->num_touch);
			if (val > cfg->num_touch) {
				input_dev = data->input_dev;
				if (input_dev) {
					for (i = cfg->num_touch; i < val; i++) {
						input_mt_slot(input_dev, i);
						input_mt_report_slot_state(input_dev, MT_TOOL_FINGER, 0);
					}
					mxt_input_sync(data);
				}
			}
		}
	}
	return 0;
}

static int mxt_set_t9_t100_cfg(void *pl_dev,int state,unsigned long unset)
{
	struct plug_interface *pl = pl_dev;
	struct mxt_data *data = pl->dev;
	struct device *dev = &data->client->dev;
	struct plug_config *dcfg = &pl->config;
	struct t9_t100_config *cfg;

	if (state >= dcfg->num_t9_t100_config) {
		dev_err(dev, "mxt_set_t9_t100_cfg: invalid t9/t100 state %d\n",state);
		return -EINVAL;
	} else {
		cfg = &dcfg->t9_t100_cfg[state];
		if (data->T9_reportid_min)
			return mxt_set_obj_t9(data,cfg,unset);
		else if (data->T100_reportid_min)
			return mxt_set_obj_t100(data,cfg,unset);
		else {
			dev_err(dev, "mxt_set_t9_t100_cfg: t9/t100 state %d not been set\n",state);
			return -EINVAL;
		}
	}

	return 0;
}

static int mxt_set_obj_t55(struct mxt_data *data,struct t55_config *cfg)
{
	struct device *dev = &data->client->dev;
	u16 reg;

	if (!data->T55_address)
		return 0;

	dev_info2(dev, "mxt set t55 (0x%x)\n",
			cfg->ctrl);

	reg = data->T55_address;
	__mxt_write_reg(data->client, reg ,sizeof(struct t55_config), cfg);

	return 0;
}

static int mxt_set_t55_adp_thld(void *pl_dev, int state)
{
	struct plug_interface *pl = pl_dev;
	struct mxt_data *data = pl->dev;
	struct device *dev = &data->client->dev;
	struct plug_config *cfg = &pl->config;
	struct t55_config config;

	if (!data->T55_address)
		return -ENODEV;

	dev_dbg2(dev, "set t55 state %d\n",
			state);

	if (state >= cfg->num_t55_config) {
		dev_err(dev, "mxt_set_t55_cfg: invalid t55 state %d\n", state);
		return -EINVAL;
	} else {
		memcpy(&config, &cfg->t55_cfg[state], sizeof(struct t55_config));
		return mxt_set_obj_t55(data, &config);
	}
}

static int mxt_set_obj_t61(struct mxt_data *data,struct t61_config *cfg,int id)
{
	struct device *dev = &data->client->dev;
	u16 reg;

	dev_info2(dev, "mxt set t61 (0x%x 0x%x 0x%x) period %d\n",
			cfg->ctrl,
			cfg->cmd,
			cfg->mode,
			cfg->period);

	reg = data->T61_address + id * sizeof(*cfg);
	__mxt_write_reg(data->client, reg ,sizeof(struct t61_config), cfg);

	return 0;
}

static int mxt_set_t61_timer(void *pl_dev, bool enable, int id)
{
	struct plug_interface *pl = pl_dev;
	struct mxt_data *data = pl->dev;
	struct device *dev = &data->client->dev;
	struct plug_config *cfg = &pl->config;
	struct t61_config config;

	if (!data->T61_address)
		return -ENODEV;

	if (id >= cfg->num_t61_config) {
		dev_err(dev, "mxt_set_t61_cfg: invalid t61 id %d\n", id);
		return -EINVAL;
	} else {
		memcpy(&config, &cfg->t61_cfg[id], sizeof(struct t61_config));

		if (enable)
			config.ctrl |= MXT_T61_CTRL_EN|MXT_T61_CTRL_RPTEN;
		else
			config.ctrl &= ~(MXT_T61_CTRL_EN|MXT_T61_CTRL_RPTEN);
		return mxt_set_obj_t61(data, &config, id);
	}
}

static int mxt_set_obj_t65(struct mxt_data *data,struct t65_config *cfg,unsigned long unset)
{
	struct device *dev = &data->client->dev;
	u16 reg;

	if (!data->T65_address)
		return 0;

	dev_info2(dev, "mxt set t65 (0x%x 0x%x 0x%x) unset 0x%lx\n",
			cfg->ctrl,
		cfg->grad_thr,
		cfg->lpfilter,
		unset);

	reg = data->T65_address;
	if (!unset)
		__mxt_write_reg(data->client, reg ,sizeof(struct t65_config), cfg);
	else {
		if (!test_bit(MXT_T65_MASK_CTRL,&unset))
			mxt_write_object(data,MXT_PROCI_LENSBENDING_T65,MXT_T65_CTRL,cfg->ctrl);

		if (!test_bit(MXT_T65_MASK_GRADTHR,&unset))
			mxt_write_object(data,MXT_PROCI_LENSBENDING_T65,MXT_T65_GRADTHR,cfg->grad_thr);
		if (!test_bit(MXT_T65_MASK_LPFILTER,&unset))
			mxt_write_object(data,MXT_PROCI_LENSBENDING_T65,MXT_T65_LPFILTER,cfg->lpfilter);
	}
	return 0;
}

static int mxt_set_t65_cfg(void *pl_dev, int state, unsigned long unset)
{
	struct plug_interface *pl = pl_dev;
	struct mxt_data *data = pl->dev;
	struct device *dev = &data->client->dev;
	struct plug_config *cfg = &pl->config;
	struct t65_config config;

	if (!data->T65_address)
		return -ENODEV;

	dev_dbg2(dev, "set t65 state %d, unset 0x%lx\n",
			state,
			unset);

	if (state >= cfg->num_t65_config) {
		dev_err(dev, "mxt_set_t65_cfg: invalid t65 state %d\n", state);
		return -EINVAL;
	} else {
		memcpy(&config, &cfg->t65_cfg[state], sizeof(struct t65_config));
		return mxt_set_obj_t65(data, &config, unset);
	}
}

static int mxt_set_obj_t80(struct mxt_data *data,struct t80_config *cfg,unsigned long unset)
{
	struct device *dev = &data->client->dev;
	u16 reg;
	u16 offset;

	if (!data->T80_address)
		return 0;

	dev_info2(dev, "mxt set t80 (0x%x 0x%x 0x%x 0x%x 0x%x) unset 0x%lx\n",
		cfg->ctrl,
		cfg->comp_gain,
		cfg->target_delta,
		cfg->compthr,
		cfg->atchthr,
		unset);

	reg = data->T80_address;
	if (!unset)
		__mxt_write_reg(data->client, reg ,sizeof(struct t80_config), cfg);
	else {
		if (!test_bit(MXT_T80_MASK_CTRL,&unset))
			mxt_write_object(data,MXT_PROCI_RETRANSMISSIONCOMPENSATION_T80,MXT_T80_CTRL,cfg->ctrl);

		offset = offsetof(struct t80_config,comp_gain);
		if (!test_bit(MXT_T80_MASK_COMP_GAIN,&unset))
			__mxt_write_reg(data->client, reg + offset,sizeof(struct t80_config)- offset, &cfg->comp_gain);
	}
	return 0;
}

static int mxt_set_t80_cfg(void *pl_dev, int state, unsigned long unset)
{
	struct plug_interface *pl = pl_dev;
	struct mxt_data *data = pl->dev;
	struct device *dev = &data->client->dev;
	struct plug_config *cfg = &pl->config;
	struct t80_config config;

	if (!data->T80_address)
		return -ENODEV;

	dev_dbg2(dev, "set t80 state %d, unset 0x%lx\n",
			state,
			unset);

	if (state >= cfg->num_t80_config) {
		dev_err(dev, "mxt_set_t80_cfg: invalid t80 state %d\n", state);
		return -EINVAL;
	} else {
		memcpy(&config, &cfg->t80_cfg[state], sizeof(struct t80_config));
		return mxt_set_obj_t80(data, &config, unset);
	}
}

static int mxt_set_obj_cfg(void *pl_dev, struct reg_config *config, u8 *stack_buf, unsigned long flag)
{
	struct plug_interface *pl = pl_dev;
	struct mxt_data *data = pl->dev;
	struct device *dev = &data->client->dev;
	struct mxt_object *object;
	u16 reg;
	u8 old_buf[255];
	int ret;
	int i;

	dev_info2(dev, "mxt set t%d offset %d, len %d mask 0x%lx, flag 0x%lx\n",
		config->reg,
		config->offset,
		config->len,
		config->mask,
		config->flag);

	if (flag && config->flag){
		if (!(flag & config->flag)){
			dev_err(&data->client->dev, "Skip request: reg %d off %d len %d flag(0x%lx,0x%lx,0x%lx)\n",
				config->reg,config->offset,config->len,
				flag, config->flag, flag & config->flag);
			return 0;
		}
	}

	if (config->len == 0){
		dev_err(&data->client->dev, "Skip zero request: reg %d off %d len %d\n",
			config->reg,config->offset,config->len);
		return 0;
	}

	print_hex_dump(KERN_INFO, "[mxt]", DUMP_PREFIX_NONE, 16, 1,
			   config->buf, config->len, false);

	object = mxt_get_object(data, config->reg);
	if (!object){
		dev_err(&data->client->dev, "Object not found: reg %d off %d len %d\n",
			config->reg,config->offset,config->len);
		return -EINVAL;
	}
	if (config->offset >= (object->size) * (object->instances)) {
		dev_err(&data->client->dev, "Tried to write outside object T%d"
			" offset:%d, size:%d\n", config->reg, config->offset, object->size);
		return -EINVAL;
	}

	reg = object->start_address;
	if (!reg){
		dev_err(&data->client->dev, "Object address not found: reg %d off %d len %d\n",
			config->reg,config->offset,config->len);
		return -EINVAL;
	}

	if (config->len > sizeof(old_buf)){
		dev_err(&data->client->dev, "Config data too long: reg %d off %d len %d\n",
			config->reg,config->offset,config->len);
		return -EINVAL;
	}

	reg += config->offset;
	dev_info2(dev, "mxt set address %d\n",reg);
	if (stack_buf || config->mask){
		ret = __mxt_read_reg(data->client, reg, config->len, old_buf);
		if (ret){
			dev_err(&data->client->dev, "Config read reg failed: reg %d off %d len %d\n",
				config->reg,config->offset,config->len);
			return ret;
		}
		if (config->mask){
			for (i = 0; i < config->len; i++){
				config->buf[i] &= config->mask;
				config->buf[i] |= old_buf[i] & ~config->mask;
			}
		}
	}

	ret = __mxt_write_reg(data->client, reg, config->len, config->buf);

	if (stack_buf)
		memcpy(stack_buf, old_buf, config->len);

	return ret;
}

static int mxt_get_init_cfg(struct mxt_data *data)
{
	struct device *dev = &data->client->dev;
	struct plug_interface *pl = &data->plug_in;
	struct mxt_config *dcfg = &pl->init_cfg;
	int error;

	//read t7 parameter

	//read t8 parameter
	error = mxt_get_init_config_t8(data,&dcfg->t8);
	if (error) {
		dev_err(dev, "Failed to read T8 parameter %d\n", error);
		return -EIO;
	}
	//read t9 parameter
	if (data->T9_reportid_min) {
		error = mxt_get_init_config_t9(data,&dcfg->t9_t100);
		if (error) {
			dev_err(dev, "Failed to read T9 parameter %d\n", error);
			return -EIO;
		}
	}

	//read t100 parameter
	if (data->T100_reportid_min) {
		error = mxt_get_init_config_t100(data,&dcfg->t9_t100);
		if (error) {
			dev_err(dev, "Failed to read T100 parameter %d\n", error);
			return -EIO;
		}
	}

	//read t15 parameter
	if (data->T15_reportid_min) {
		error = mxt_get_init_config_t15(data,&dcfg->t15);
		if (error) {
			dev_err(dev, "Failed to read T15 parameter %d\n", error);
			return -EIO;
		}
	}
	//read t38 parameter
	error = mxt_get_init_config_t38(data,&dcfg->t38);
	if (error) {
		dev_err(dev, "Failed to read T38 parameter %d\n", error);
		return -EIO;
	}

	//read t40 parameter
	if (data->T40_address) {
		error = mxt_get_init_config_t40(data,&dcfg->t40);
		if (error) {
			dev_err(dev, "Failed to read T40 parameter %d\n", error);
			return -EIO;
		}
	}
	//read t42 parameter

	//read t55 parameter
	if (data->T55_address) {
		error = mxt_get_init_config_t55(data,&dcfg->t55);
		if (error) {
			dev_err(dev, "Failed to read T55 parameter %d\n", error);
			return -EIO;
		}
	}
	//read t61 parameter
	if (data->T61_address) {
		error = mxt_get_init_config_t61(data,&dcfg->t61[0],min_t(int , data->T61_instances, T61_MAX_INSTANCE_NUM));
		if (error) {
			dev_err(dev, "Failed to read T61 parameter %d\n", error);
			return -EIO;
		}
	}
	//read t65 parameter
	if (data->T65_address) {
		error = mxt_get_init_config_t65(data,&dcfg->t65);
		if (error) {
			dev_err(dev, "Failed to read T65 parameter %d\n", error);
			return -EIO;
		}
	}
	//read t80 parameter
	if (data->T80_address) {
		error = mxt_get_init_config_t80(data,&dcfg->t80);
		if (error) {
			dev_err(dev, "Failed to read T80 parameter %d\n", error);
			return -EIO;
		}
	}

	config_matrix_init(dcfg,data->info.matrix_xsize,data->info.matrix_ysize);
	dcfg->dev = &data->client->dev;
	dcfg->max_x = data->max_x;
	dcfg->max_y = data->max_y;

	return 0;
}

static int mxt_get_phone_status(struct plug_interface *pl, unsigned long pl_flag)
{
	//phone on return -EBUSY, else return 0

	/*
	if (g_phone_on){
		return -EBUSY;
	}
	*/
	return 0;
}

static void mxt_plugin_pre_process(struct plug_interface *pl, bool in_boot)
{
	struct plug_observer *obs = &pl->observer;

	if (!pl->inited)
		return;

	if (test_flag(PL_STATUS_FLAG_FORCE_STOP,&obs->flag)) {
		set_and_clr_flag(PL_STATUS_FLAG_STOP, PL_STATUS_FLAG_FORCE_STOP, &obs->flag);
		return;
	}

	if (test_flag(PL_STATUS_FLAG_STOP|PL_STATUS_FLAG_PAUSE|PL_STATUS_FLAG_SUSPEND,&obs->flag))
		return;

	if (!in_boot) {
		if (mxt_get_phone_status(pl, pl->observer.flag) == -EBUSY){
			set_flag(PL_STATUS_FLAG_PHONE_ON,&obs->flag);
		}else{
			clear_flag(PL_STATUS_FLAG_PHONE_ON,&obs->flag);
		}
		if (!test_flag(PL_STATUS_FLAG_PAUSE_AC,&obs->flag)) {
			if (pl->ac->pre_process)
				pl->ac->pre_process(pl->ac, pl->observer.flag);
		}

		if (!test_flag(PL_STATUS_FLAG_PAUSE_CAL,&obs->flag)) {
			if (pl->cal->pre_process)
				pl->cal->pre_process(pl->cal, pl->observer.flag);
		}

		if (!test_flag(PL_STATUS_FLAG_PAUSE_PI,&obs->flag)){
			if (pl->pi->pre_process)
				pl->pi->pre_process(pl->pi, pl->observer.flag);
		}
	}
}

static long mxt_plugin_post_process(struct plug_interface *pl, bool in_boot)
{
	struct plug_observer *obs = &pl->observer;
	unsigned long interval0,interval1;

	if (!pl->inited)
		return MAX_SCHEDULE_TIMEOUT;

	if (test_flag(PL_STATUS_FLAG_FORCE_STOP,&obs->flag)) {
		set_and_clr_flag(PL_STATUS_FLAG_STOP, PL_STATUS_FLAG_FORCE_STOP, &obs->flag);
		return MAX_SCHEDULE_TIMEOUT;
	}

	if (test_flag(PL_STATUS_FLAG_STOP|PL_STATUS_FLAG_PAUSE|PL_STATUS_FLAG_SUSPEND,&obs->flag))
		return MAX_SCHEDULE_TIMEOUT;

	interval0 = interval1 = MAX_SCHEDULE_TIMEOUT;
	if (!in_boot){
		if (!test_flag(PL_STATUS_FLAG_PAUSE_AC,&obs->flag)){
			if (pl->ac->post_process)
				interval0 = pl->ac->post_process(pl->ac, pl->observer.flag);
		}

		if (!test_flag(PL_STATUS_FLAG_PAUSE_CAL,&obs->flag)) {
			if (pl->cal->post_process) {
				interval1 = pl->cal->post_process(pl->cal, pl->observer.flag);
				interval0 = min_t(unsigned long,interval0,interval1);
			}
		}
		if (!test_flag(PL_STATUS_FLAG_PAUSE_PI,&obs->flag)){
			if (pl->pi->post_process){
				interval1 = pl->pi->post_process(pl->pi, pl->observer.flag);
				interval0 = min_t(unsigned long,interval0,interval1);
			}
		}
	}
	return min_t(unsigned long,interval0,interval1);
}

static void mxt_plugin_hook_t6(struct plug_interface *pl, u8 status)
{
	struct plug_observer *obs = &pl->observer;

	if (!pl->inited)
		return;

	if (test_flag(PL_STATUS_FLAG_STOP,&obs->flag))
		return;

	if (status) {
		set_flag(PL_STATUS_FLAG_NOSUSPEND, &pl->observer.flag);
		if (status & MXT_T6_STATUS_RESET) //default t8 is open
			set_and_clr_flag(PL_STATUS_FLAG_T8_SET, PL_STATUS_FLAG_LOW_MASK, &pl->observer.flag);
	} else
		clear_flag(PL_STATUS_FLAG_NOSUSPEND, &pl->observer.flag);

	if (pl->cal->hook_t6)
		pl->cal->hook_t6(pl->cal, status);

	if (pl->ac->hook_t6)
		pl->ac->hook_t6(pl->ac, status);
	if (pl->pi->hook_t6)
		pl->pi->hook_t6(pl->pi, status);
}

static void mxt_plugin_hook_t9(struct plug_interface *pl, int id, int x, int y, u8 status)
{
	struct plug_observer *obs = &pl->observer;

	if (!pl->inited)
		return;

	if (test_flag(PL_STATUS_FLAG_STOP,&obs->flag))
		return;

	if (pl->cal->hook_t9)
		pl->cal->hook_t9(pl->cal, id, x, y, status);

	if (pl->ac->hook_t9)
		pl->ac->hook_t9(pl->ac, id, x, y, status);
}

static int mxt_plugin_hook_t61(struct plug_interface *pl, int id, u8 status)
{
	struct plug_observer *obs = &pl->observer;
	int ret = -EINVAL;
	if (!pl->inited)
		return ret;

	if (test_flag(PL_STATUS_FLAG_STOP,&obs->flag))
		return ret;

	if (pl->cal->hook_t61)
		pl->cal->hook_t61(pl->cal, id, status);

	if (pl->ac->hook_t61)
		pl->ac->hook_t61(pl->ac, id, status);

	if (pl->pi->hook_t61)
		ret = pl->pi->hook_t61(pl->pi, id, status, obs->flag);

	return ret;
}

static void mxt_plugin_hook_t72(struct plug_interface *pl, u8* msg)
{
	struct plug_observer *obs = &pl->observer;

	if (!pl->inited)
		return;

	if (test_flag(PL_STATUS_FLAG_STOP,&obs->flag))
		return;

	if (pl->cal->hook_t72)
		pl->cal->hook_t72(pl->cal, msg);

	if (pl->ac->hook_t72)
		pl->ac->hook_t72(pl->ac, msg);
}

static void mxt_plugin_hook_reset_slots(struct plug_interface *pl)
{
	struct plug_observer *obs = &pl->observer;

	if (!pl->inited)
		return;

	if (test_flag(PL_STATUS_FLAG_STOP,&obs->flag))
		return;

	if (pl->cal->hook_reset_slots)
		pl->cal->hook_reset_slots(pl->cal);

	if (pl->ac->hook_reset_slots)
		pl->ac->hook_reset_slots(pl->ac);
}

static void mxt_plugin_hook_t100(struct plug_interface *pl, int id, int x, int y, u8 status)
{
	struct plug_observer *obs = &pl->observer;

	if (!pl->inited)
		return;

	if (test_flag(PL_STATUS_FLAG_STOP,&obs->flag))
		return;

	if (pl->cal->hook_t100)
		pl->cal->hook_t100(pl->cal, id, x, y, status);

	if (pl->ac->hook_t100)
		pl->ac->hook_t100(pl->ac, id, x, y, status);
}

static int mxt_plugin_hook_set_t7(struct plug_interface *pl, bool sleep)
{
	struct plug_observer *obs = &pl->observer;
	struct mxt_data *data;
	struct device *dev;

	int wait = 10;

	if (!pl->inited)
		return 0;

	data = pl->dev;
	dev = &data->client->dev;

	if (test_flag(PL_STATUS_FLAG_STOP,&obs->flag))
		return 0;

	if (sleep) {
		do{
			if (!(test_flag(PL_STATUS_FLAG_NOSUSPEND,&obs->flag)))
				break;

			dev_info(dev, "mxt_plugin_hook_set_t7 wait flag 0x%lx, wait %d\n",
				obs->flag, wait);

			msleep(20);
		}while(--wait >= 0);

		if (test_flag(PL_STATUS_FLAG_NOSUSPEND,&obs->flag))
			return -EACCES;
	}

	return 0;
}

static int mxt_plugin_hook_reg_init(struct plug_interface *pl, u8 *config_mem, size_t config_mem_size, int cfg_start_ofs)
{
	struct mxt_data *data;
	struct device *dev;
	size_t len;

	if (!pl->inited)
		return -ENODEV;

	data = pl->dev;
	dev = &data->client->dev;

	dev_info(dev, "mxt_plugin_hook_reg_init\n");
	len = len;

#if defined(CONFIG_MXT_T38_SKIP_LEN_AT_UPDATING)
	if (data->T38_address < cfg_start_ofs) {
		dev_err(dev, "Bad T8 address, T8addr = %x, config offset %x\n",
			data->T7_address, cfg_start_ofs);
		return -EINVAL;
	} else {
		len = min_t(int, config_mem_size, CONFIG_MXT_T38_SKIP_LEN_AT_UPDATING);
		len = min_t(int, len, sizeof(pl->init_cfg.t38.data));
		memcpy(config_mem + data->T38_address - cfg_start_ofs, pl->init_cfg.t38.data, len);
	}
#endif

	return 0;
}

static int mxt_plugin_cal_t37_check_and_calibrate(struct plug_interface *pl, bool check_sf)
{
	int ret = -EBUSY;

	if (!pl->inited)
		return -ENODEV;

	if (pl->cal->check_and_calibrate)
		ret = pl->cal->check_and_calibrate(pl->cal, check_sf ,pl->observer.flag);
	return ret;
}

static int mxt_plugin_start(struct plug_interface *pl, bool resume)
{
	struct plug_observer *obs = &pl->observer;
	int ret = 0;

	if (!pl->inited)
		return 0;

	if (test_flag(PL_STATUS_FLAG_STOP,&obs->flag))
		return 0;

	if (resume)
		set_and_clr_flag(PL_STATUS_FLAG_RESUME|PL_STATUS_FLAG_POWERUP,PL_STATUS_FLAG_SUSPEND, &obs->flag);
	else
		clear_flag(PL_STATUS_FLAG_PAUSE, &obs->flag);

	if (pl->cal->start)
		pl->cal->start(pl->cal,resume);

	if (pl->ac->start)
		pl->ac->start(pl->ac,resume);

	if (pl->pi->start)
		pl->pi->start(pl->pi,resume);

	if (resume)
		clear_flag(PL_STATUS_FLAG_RESUME, &obs->flag);

	return ret;
}


static int mxt_plugin_stop(struct plug_interface *pl, bool suspend)
{
	struct plug_observer *obs = &pl->observer;
	int ret = 0;

	if (!pl->inited)
		return 0;

	if (test_flag(PL_STATUS_FLAG_STOP,&obs->flag))
		return 0;

	if (suspend){
#if defined(CONFIG_MXT_TRIGGER_PI_PRE_PROCESS_AT_FIRST_POWERUP)
		//extern varible to control plugin
		if (!test_flag(PL_STATUS_FLAG_PAUSE_PI|PL_STATUS_FLAG_POWERUP,&obs->flag)){
			if (pl->pi->pre_process)
				pl->pi->pre_process(pl->pi, pl->observer.flag);
		}
#endif
		set_and_clr_flag(PL_STATUS_FLAG_SUSPEND, PL_STATUS_FLAG_RESUME, &obs->flag);
	}

	if (pl->cal->stop)
		pl->cal->stop(pl->cal);

	if (pl->ac->stop)
		pl->ac->stop(pl->ac);

	if (pl->pi->stop)
		pl->pi->stop(pl->pi);

	if (!suspend)
		set_flag(PL_STATUS_FLAG_PAUSE, &obs->flag);

	return ret;
}

static int mxt_plugin_force_stop(struct plug_interface *pl)
{
	struct mxt_data *data;
	struct device *dev;
	struct plug_observer *obs;
	int wait = 25;

	if (!pl->inited)
		return 0;

	data = pl->dev;
	dev = &data->client->dev;
	obs = &pl->observer;

	dev_info(dev, "mxt_plugin_force_stop\n");

	if (test_flag(PL_STATUS_FLAG_STOP,&obs->flag))
		return 0;

	set_flag(PL_STATUS_FLAG_FORCE_STOP,&obs->flag);

	if (pl->active_thread)
	   pl->active_thread(pl->dev,MXT_EVENT_EXTERN);

	do{
		if (test_flag(PL_STATUS_FLAG_CAL_END|PL_STATUS_FLAG_PAUSE,&obs->flag)){
			set_and_clr_flag(PL_STATUS_FLAG_STOP, PL_STATUS_FLAG_FORCE_STOP, &obs->flag);
			return 0;
		}

		if (test_flag(PL_STATUS_FLAG_STOP,&obs->flag))
			return 0;

		dev_info(dev, "mxt_plugin_force_stop wait flag 0x%lx, wait %d\n", obs->flag, wait);

		msleep(100);
	}while(--wait >= 0);

	set_and_clr_flag(PL_STATUS_FLAG_STOP, PL_STATUS_FLAG_FORCE_STOP, &obs->flag);
	return -EBUSY;
}

static bool valid_config(void *pcfg, int len, u8 check_val)
{
	u8 *dt = (u8 *)pcfg;
	int i;

	for (i = 0; i < len; i++){
		if (dt[i] != check_val)
			return true;
	}

	return false;
}

static struct t8_config mxt_t8_cfg[] = {
	//T8_HALT
	{255,1,0,0},
	//T8_NORMAL
	{-1,-1,-1,-1 /*0,25,15,-30*/},  //-1 means normal setting will be readout from t8 at init
	//T8_NOISE
	{0,25,10,-1},
	//T8_VERY_NOISE
	{0,35,20,-1},
	//T8_MIDDLE
	{0,15,10,0},
	//T8_WEAK_PALM, each one repeat 4 times
	//{-1,-1,10,10},
	{-1,-1,0,0},
};

static struct t9_t100_config mxt_t9_t100_cfg[T9_T100_CONFIG_NUM] = {
	//t38 will overwrite here
	//T9_T100_NORMAL
	{0},  //0 means normal setting will be readout from t9/t100 at init
	//T9_T100_THLD_NOISE
	{0},
	//T9_T100_THLD_VERY_NOISE
	{0},
	//T9_T100_NORMAL_STEP1
	{0},
	//T9_T100_THLD_NOISE_STEP1
	{0},
	//T9_T100_THLD_VERY_NOISE_STEP1
	{0},
	//T9_T100_SINGLE_TOUCH
	{0}
};

static struct t55_config mxt_t55_cfg[T55_CONFIG_NUM] = {
	{0},
	{0}
};

static struct t61_config mxt_t61_cfg[T61_MAX_INSTANCE_NUM] = {
	{0},  //timer 0
	{0}   //timer 1
};

static struct t65_config mxt_t65_cfg[T65_CONFIG_NUM] = {
	{0},
	{0,1,{0,0,0,0,0,0,0,0},1},
};

static struct t80_config mxt_t80_cfg[T80_CONFIG_NUM] = {
	{0},
	{0x0,1,1,255,63}
};

static void mxt_plugin_thread_stopped(struct plug_interface *pl)
{
	struct mxt_data *data;
	struct device *dev;
	struct plug_observer *obs;

	if (!pl->inited)
		return;

	data = pl->dev;
	dev = &data->client->dev;
	obs = &pl->observer;

	dev_info(dev, "mxt_plugin_thread_stopped\n");

	if (test_flag(PL_STATUS_FLAG_STOP,&obs->flag))
		return;

	set_flag(PL_STATUS_FLAG_STOP, &obs->flag);
}
static int init_plugin(struct plug_interface *pl)
{
	struct plug_config *cfg = &pl->config;
	struct plug_observer *obs = &pl->observer;
	int i;

	//t8
	cfg->t8_cfg = kzalloc(sizeof(mxt_t8_cfg), GFP_KERNEL);
	if (!cfg->t8_cfg){
		return -ENOMEM;
	}
	memcpy(cfg->t8_cfg, &mxt_t8_cfg[0], sizeof(mxt_t8_cfg));
	cfg->num_t8_config = ARRAY_SIZE(mxt_t8_cfg);
	if (!valid_config(&cfg->t8_cfg[T8_NORMAL], sizeof(struct t8_config), (u8)-1)){
		memcpy(&cfg->t8_cfg[T8_NORMAL], &pl->init_cfg.t8, sizeof(struct t8_config));
		for (i = T8_WEAK_PALM; i < cfg->num_t8_config; i++){
			if (!valid_config(&cfg->t8_cfg[i], offsetof(struct t8_config,atchfrccalthr), (u8)-1)){
				memcpy(&cfg->t8_cfg[i], &pl->init_cfg.t8, offsetof(struct t8_config,atchfrccalthr));
			}
		}
	}

	//t9/t100
	cfg->t9_t100_cfg = kzalloc(sizeof(mxt_t9_t100_cfg), GFP_KERNEL);
	if (!cfg->t9_t100_cfg){
		return -ENOMEM;
	}
	memcpy(cfg->t9_t100_cfg, &mxt_t9_t100_cfg[0], sizeof(mxt_t9_t100_cfg));
	cfg->num_t9_t100_config = ARRAY_SIZE(mxt_t9_t100_cfg);
	if (!valid_config(&cfg->t9_t100_cfg[T9_T100_NORMAL], sizeof(struct t9_t100_config), 0)){
		memcpy(&cfg->t9_t100_cfg[T9_T100_NORMAL], &pl->init_cfg.t9_t100, sizeof(struct t9_t100_config));
		memcpy(&cfg->t9_t100_cfg[T9_T100_THLD_NOISE], &cfg->t9_t100_cfg[T9_T100_NORMAL], sizeof(struct t9_t100_config));
		memcpy(&cfg->t9_t100_cfg[T9_T100_THLD_VERY_NOISE], &cfg->t9_t100_cfg[T9_T100_NORMAL], sizeof(struct t9_t100_config));
		memcpy(&cfg->t9_t100_cfg[T9_T100_NORMAL_STEP1], &cfg->t9_t100_cfg[T9_T100_NORMAL], sizeof(struct t9_t100_config));
		memcpy(&cfg->t9_t100_cfg[T9_T100_THLD_NOISE_STEP1], &cfg->t9_t100_cfg[T9_T100_NORMAL], sizeof(struct t9_t100_config));
		memcpy(&cfg->t9_t100_cfg[T9_T100_THLD_VERY_NOISE_STEP1], &cfg->t9_t100_cfg[T9_T100_NORMAL], sizeof(struct t9_t100_config));

		switch(pl->init_cfg.t38.data[MXT_T38_MGWD]){
			case MXT_T38_MAGIC_WORD:
				cfg->t9_t100_cfg[T9_T100_NORMAL_STEP1].threshold = pl->init_cfg.t38.data[MXT_T38_T9_T100_THLD_NORMAL_STEP1];
				cfg->t9_t100_cfg[T9_T100_THLD_NOISE].threshold = pl->init_cfg.t38.data[MXT_T38_T9_T100_THLD_NOISE];
				break;
			default:
				;
		}
	}
	cfg->t9_t100_cfg[T9_T100_THLD_VERY_NOISE].threshold = cfg->t9_t100_cfg[T9_T100_THLD_VERY_NOISE].dualx_threshold;
	cfg->t9_t100_cfg[T9_T100_THLD_NOISE_STEP1].threshold =
		cfg->t9_t100_cfg[T9_T100_THLD_NOISE].threshold - cfg->t9_t100_cfg[T9_T100_NORMAL].threshold + cfg->t9_t100_cfg[T9_T100_NORMAL_STEP1].threshold;
	cfg->t9_t100_cfg[T9_T100_THLD_VERY_NOISE_STEP1].threshold =
		cfg->t9_t100_cfg[T9_T100_THLD_VERY_NOISE].threshold - cfg->t9_t100_cfg[T9_T100_NORMAL].threshold + cfg->t9_t100_cfg[T9_T100_NORMAL_STEP1].threshold;

	memcpy(&cfg->t9_t100_cfg[T9_T100_SINGLE_TOUCH], &cfg->t9_t100_cfg[T9_T100_NORMAL], sizeof(struct t9_t100_config));
	cfg->t9_t100_cfg[T9_T100_SINGLE_TOUCH].num_touch = 2;

	//t42

	//t55
	cfg->t55_cfg = kzalloc(sizeof(mxt_t55_cfg), GFP_KERNEL);
	if (!cfg->t55_cfg){
		return -ENOMEM;
	}
	memcpy(cfg->t55_cfg, &mxt_t55_cfg[0], sizeof(mxt_t55_cfg));
	cfg->num_t55_config = ARRAY_SIZE(mxt_t55_cfg);
	if (!valid_config(&cfg->t55_cfg[T55_NORMAL], sizeof(struct t55_config), 0)){
		memcpy(&cfg->t55_cfg[T55_NORMAL], &pl->init_cfg.t55, sizeof(struct t55_config));
	}

	//t61
	cfg->t61_cfg = kzalloc(sizeof(mxt_t61_cfg), GFP_KERNEL);
	if (!cfg->t61_cfg){
		return -ENOMEM;
	}
	memcpy(cfg->t61_cfg, &mxt_t61_cfg[0], sizeof(mxt_t61_cfg));
	cfg->num_t61_config = ARRAY_SIZE(mxt_t61_cfg);
	for (i = 0; i < cfg->num_t61_config; i++){
		if (i >= T61_MAX_INSTANCE_NUM)
			break;

		if (!valid_config(&cfg->t61_cfg[i], sizeof(struct t61_config), 0)){
			memcpy(&cfg->t61_cfg[i], &pl->init_cfg.t61[i], sizeof(struct t61_config));
		}
	}
	//t65
	cfg->t65_cfg = kzalloc(sizeof(mxt_t65_cfg), GFP_KERNEL);
	if (!cfg->t65_cfg){
		return -ENOMEM;
	}
	memcpy(cfg->t65_cfg, &mxt_t65_cfg[0], sizeof(mxt_t65_cfg));
	cfg->num_t65_config = ARRAY_SIZE(mxt_t65_cfg);
	if (!valid_config(&cfg->t65_cfg[T65_NORMAL], sizeof(struct t65_config), 0)){
		memcpy(&cfg->t65_cfg[T65_NORMAL], &pl->init_cfg.t65, sizeof(struct t65_config));
	}

	//t80
	cfg->t80_cfg = kzalloc(sizeof(mxt_t80_cfg), GFP_KERNEL);
	if (!cfg->t80_cfg){
		return -ENOMEM;
	}
	memcpy(cfg->t80_cfg, &mxt_t80_cfg[0], sizeof(mxt_t80_cfg));
	cfg->num_t80_config = ARRAY_SIZE(mxt_t80_cfg);
	if (!valid_config(&cfg->t80_cfg[T80_NORMAL], sizeof(struct t80_config), 0)){
		memcpy(&cfg->t80_cfg[T80_NORMAL], &pl->init_cfg.t80, sizeof(struct t80_config));
	}
	if (!valid_config(&cfg->t80_cfg[T80_LOW_GAIN], sizeof(struct t80_config), 0)){
		memcpy(&cfg->t80_cfg[T80_LOW_GAIN], &pl->init_cfg.t80, sizeof(struct t80_config));
	}

#if defined(CONFIG_MXT_CAL_T37_WORKAROUND)
	plugin_cal_init(pl->cal);
#endif
#if defined(CONFIG_MXT_AC_T72_WORKAROUND)
	plugin_ac_init(pl->ac);
#endif
#if defined(CONFIG_MXT_PROCI_PI_WORKAROUND)
	plugin_proci_init(pl->pi);
#endif
	set_and_clr_flag(/*PL_STATUS_FLAG_PAUSE_MASK*/PL_STATUS_FLAG_PAUSE_PI,PL_STATUS_FLAG_MASK, &obs->flag);
	return 0;
}

static void deinit_plugin(struct plug_interface *pl)
{
	struct plug_config *cfg = &pl->config;

	//t8
	if (cfg->t8_cfg){
		kfree(cfg->t8_cfg);
		cfg->t8_cfg = NULL;
	}

	//t9/t100
	if (cfg->t9_t100_cfg){
		kfree(cfg->t9_t100_cfg);
		cfg->t9_t100_cfg = NULL;
	}

	//t42

	//t55
	if (cfg->t55_cfg){
		kfree(cfg->t55_cfg);
		cfg->t55_cfg = NULL;
	}


	//t61
	if (cfg->t61_cfg){
		kfree(cfg->t61_cfg);
		cfg->t61_cfg = NULL;
	}

	//t65
	if (cfg->t65_cfg){
		kfree(cfg->t65_cfg);
		cfg->t65_cfg = NULL;
	}


	//t80
	if (cfg->t80_cfg){
		kfree(cfg->t80_cfg);
		cfg->t80_cfg = NULL;
	}
}
struct plugin_cal mxt_plugin_cal;
struct plugin_ac mxt_plugin_ac;
struct plugin_proci mxt_plugin_pi;

static int mxt_plugin_pre_init(struct mxt_data *data)
{
	struct plug_interface *pl = &data->plug_in;
	struct device *dev = &data->client->dev;
	int error;

	dev_info(dev, "%s: plugin version 0x%x\n",
			__func__,PLUG_VERSION);

	if (!data->object_table)
		return -ENODEV;

	if (pl->inited) {
		dev_err(dev, "%s: plugin has been initilized\n",
				__func__);
		return -EEXIST;
	}

	pl->dev = data;
	pl->cal = &mxt_plugin_cal;
	pl->ac = &mxt_plugin_ac;
	pl->pi = &mxt_plugin_pi;

	error = mxt_get_init_cfg(data);
	if (error) {
		dev_err(dev, "pre init plugin get default config failed\n");
		return error;
	}

	return 0;
}

static int mxt_plugin_init(struct mxt_data *data)
{
	struct plug_interface *pl = &data->plug_in;
	struct device *dev = &data->client->dev;
	int error;

	dev_info(dev, "%s: plugin version 0x%x\n",
			__func__,PLUG_VERSION);

	if (!data->object_table)
		return -ENODEV;

	if (pl->inited) {
		dev_err(dev, "%s: plugin has been initilized\n",
				__func__);
		return -EEXIST;
	}

	pl->dev = data;
	pl->cal = &mxt_plugin_cal;
	pl->ac = &mxt_plugin_ac;
	pl->pi = &mxt_plugin_pi;
	pl->active_thread = mxt_active_proc_thread;

	error = mxt_get_init_cfg(data);
	if (error) {
		dev_err(dev, "init plugin get default config failed\n");
		return error;
	}

	error = init_plugin(pl);
	if (error){
		dev_err(dev, "init plugin failed\n");
		deinit_plugin(pl);
		return error;
	}

	if (pl->cal->init) {
		pl->cal->dev = (void *)pl;
		pl->cal->dcfg = &pl->init_cfg;
		pl->cal->set_and_clr_flag = plug_set_and_clr_flag;
		pl->cal->set_t6_cal= mxt_set_t6_cal;
		pl->cal->set_t8_cfg = mxt_set_t8_cfg;
		pl->cal->set_t9_t100_cfg = mxt_set_t9_t100_cfg;
		//pl->cal->set_t42_cfg = mxt_set_t42_cfg;
		pl->cal->set_t55_adp_thld = mxt_set_t55_adp_thld;
		pl->cal->set_t61_timer = mxt_set_t61_timer;
		pl->cal->set_t65_cfg = mxt_set_t65_cfg;
		pl->cal->set_t80_cfg = mxt_set_t80_cfg;
		if (pl->cal->init(pl->cal) != 0){
			dev_err(dev, "init cal plugin failed, disable this plugin\n");
			pl->cal->deinit(pl->cal);
			memset(pl->cal, 0, sizeof(struct plugin_cal));
		}
	} else {
		dev_info(dev, "doesn't get any cal plugin\n");
		memset(pl->cal, 0, sizeof(struct plugin_cal));
	}

	if (pl->ac->init) {
		pl->ac->dev = (void *)pl;
		pl->ac->dcfg = &pl->init_cfg;
		pl->ac->set_and_clr_flag = plug_set_and_clr_flag;
		pl->ac->set_t6_cal= mxt_set_t6_cal;
		pl->ac->set_t8_cfg = mxt_set_t8_cfg;
		pl->ac->set_t9_t100_cfg = mxt_set_t9_t100_cfg;
		pl->ac->set_t55_adp_thld = mxt_set_t55_adp_thld;
		pl->ac->set_t61_timer = mxt_set_t61_timer;
		pl->ac->set_t65_cfg = mxt_set_t65_cfg;
		pl->ac->set_t80_cfg = mxt_set_t80_cfg;
		if (pl->ac->init(pl->ac) != 0){
			dev_err(dev, "init ac plugin failed, disable this plugin\n");
			pl->ac->deinit(pl->ac);
			memset(pl->ac, 0, sizeof(struct plugin_ac));
		}
	} else {
		dev_info(dev, "doesn't get any ac plugin\n");
		memset(pl->ac, 0, sizeof(struct plugin_ac));
	}

	if (pl->pi->init){
		pl->pi->dev = (void *)pl;
		pl->pi->dcfg = &pl->init_cfg;
		pl->pi->set_and_clr_flag = plug_set_and_clr_flag;
		pl->pi->set_obj_cfg = mxt_set_obj_cfg;
		if (pl->pi->init(pl->pi) != 0){
			dev_err(dev, "init pi plugin failed, disable this plugin\n");
			pl->pi->deinit(pl->pi);
			memset(pl->pi, 0, sizeof(struct plugin_proci));
		}
	}else{
		dev_info(dev, "doesn't get any pi plugin\n");
		memset(pl->pi, 0, sizeof(struct plugin_proci));
	}

	if (pl->cal->init || pl->ac->init || pl->pi->init){
		pl->inited = true;

		if (pl->cal->init){
			mxt_plugin_hook_t6(pl,MXT_T6_STATUS_RESET|MXT_T6_STATUS_CAL);//init as reset status
			mxt_plugin_hook_t6(pl,0);
		}
	}
	return 0;
}

static void mxt_plugin_deinit(struct plug_interface *pl)
{
	struct plug_observer *obs = &pl->observer;

	printk(KERN_ERR "mxt_plugin_deinit\n");
	if (!pl->inited)
		return;

	if (!test_flag(PL_STATUS_FLAG_STOP, &obs->flag)){
		printk(KERN_ERR "mxt_plugin_deinit not stop\n");
		set_flag(PL_STATUS_FLAG_STOP, &obs->flag);
	}

	pl->inited = false;

	if (pl->cal->deinit){
		pl->cal->deinit(pl->cal);
		memset(pl->cal, 0, sizeof(struct plugin_cal));
	}

	if (pl->ac->deinit){
		pl->ac->deinit(pl->ac);
		memset(pl->ac, 0, sizeof(struct plugin_ac));
	}

	if (pl->pi->deinit){
		pl->pi->deinit(pl->pi);
		memset(pl->pi, 0, sizeof(struct plugin_proci));
	}

	deinit_plugin(pl);
}

static ssize_t mxt_plugin_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct mxt_data *data = dev_get_drvdata(dev);
	struct plug_interface *pl = &data->plug_in;
	struct plug_config *cfg = &pl->config;
	struct plug_observer *obs = &pl->observer;
	int i;

	dev_info(dev, "[mxt]PLUG_VERSION: 0x%x\n",PLUG_VERSION);

	if (!pl->inited)
		return -ENODEV;

	dev_info(dev, "[mxt]Plug cfg :\n");

	dev_info(dev, "[mxt]dcfg: t9_t100 start(%u,%u) size(%u,%u)\n",
			pl->init_cfg.t9_t100.x0,
			pl->init_cfg.t9_t100.y0,
			pl->init_cfg.t9_t100.xsize,
			pl->init_cfg.t9_t100.ysize);

	dev_info(dev, "[mxt]dcfg: t15 start(%u,%u) size(%u,%u)\n",
			pl->init_cfg.t15.x0,
			pl->init_cfg.t15.y0,
			pl->init_cfg.t15.xsize,
			pl->init_cfg.t15.ysize);

	for (i = 0; i < MX_SUM; i++) {
		struct rect *m = &pl->init_cfg.m[i];
		dev_info(dev, "[mxt]dcfg: Matrix %d (%d,%d)~(%d,%d)\n",
				i,
				m->x0,
				m->y0,
				m->x1,
				m->y1);
	}

	for (i = 0; i < cfg->num_t8_config; i++) {
		struct t8_config *t8_cfg = &cfg->t8_cfg[i];
		dev_info(dev, "[mxt]t8(%d): {%u,%u,%u,%d}\n",
				i,
				t8_cfg->atchcalst,
				t8_cfg->atchcalsthr,
				t8_cfg->atchfrccalthr,
				t8_cfg->atchfrccalratio);
	}
	for (i = 0; i < cfg->num_t9_t100_config; i++) {
		struct t9_t100_config *t9_t100_cfg = &cfg->t9_t100_cfg[i];
		dev_info(dev, "[mxt]t%d(%d): {%u,%u,%u,%u,%u,%u,%u}\n",
				data->T9_reportid_min ? 9 : (data->T100_reportid_min ? 100 : 255),
				i,
				t9_t100_cfg->threshold,
				t9_t100_cfg->hysterisis,
				t9_t100_cfg->internal_threshold,
				t9_t100_cfg->internal_hysterisis,
				t9_t100_cfg->merge_threshold,
				t9_t100_cfg->merge_hysterisis,
				t9_t100_cfg->dualx_threshold);
	}
	for (i = 0; i < cfg->num_t55_config; i++) {
		struct t55_config *t55_cfg = &cfg->t55_cfg[i];
		dev_info(dev, "[mxt]t55(%d): {0x%x}\n",
				i,
				t55_cfg->ctrl);
	}
	for (i = 0; i < cfg->num_t61_config; i++) {
		struct t61_config *t61_cfg = &cfg->t61_cfg[i];
		dev_info(dev, "[mxt]t61(%d): {0x%x,0x%x,0x%x,%u}\n",
				i,
				t61_cfg->ctrl,
				t61_cfg->cmd,
				t61_cfg->mode,
				t61_cfg->period);
	}
	for (i = 0; i < cfg->num_t65_config; i++) {
		struct t65_config *t65_cfg = &cfg->t65_cfg[i];
		dev_info(dev, "[mxt]t65(%d): {0x%x,%u,%u}\n",
			i,
			t65_cfg->ctrl,
			t65_cfg->grad_thr,
			t65_cfg->lpfilter);
	}
	dev_info(dev, "[mxt]\n");
	for (i = 0; i < cfg->num_t80_config; i++) {
		struct t80_config *t80_cfg = &cfg->t80_cfg[i];
		dev_info(dev, "[mxt]t80(%d): {0x%x,%u,%u,%u,%u}\n",
				i,
				t80_cfg->ctrl,
				t80_cfg->comp_gain,
				t80_cfg->target_delta,
				t80_cfg->compthr,
				t80_cfg->atchthr);
	}
	dev_info(dev, "[mxt]\n");

	dev_info(dev, "[mxt]Plug obs :\n");
	dev_info(dev, "[mxt]status: Flag=0x%08lx\n",
			obs->flag);
	dev_info(dev, "[mxt]\n");

	if (pl->cal->show)
		pl->cal->show(pl->cal);

	if (pl->ac->show)
		pl->ac->show(pl->ac);

	if (pl->pi->show)
		 pl->pi->show(pl->pi);

	return 0;
}

static ssize_t mxt_plugin_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct mxt_data *data = dev_get_drvdata(dev);
	struct plug_interface *pl = &data->plug_in;
	struct plug_config *cfg = &pl->config;
	struct plug_observer *obs = &pl->observer;
	int config[16];
	int object,offset,ofs,i,ret;
	char name[255];

	if (!pl->inited)
		return -ENODEV;

	dev_info(dev, "[mxt]%s (%d)\n",buf,count);

	if (count > 4){
		ret = sscanf(buf, "%s %n", name, &offset);
		dev_info(dev, "name %s, offset %d, ret %d\n",name,offset,ret);
		if (ret == 1) {
			if (strncmp(name, "pl", 2) == 0) {
				dev_info(dev, "cmd 'pl': %s\n",buf + offset);
				ret = sscanf(buf + offset, "t%d%n", &object, &ofs);
				dev_info(dev, "object %d, ofs %d, ret %d\n",object,ofs,ret);
				if (count > 5 &&  ret == 1) {
					offset += ofs;
					dev_info(dev, "parse %s\n",buf + offset);
					switch (object) {
						case 8:
							ret = sscanf(buf + offset, "(%d): {%d,%d,%d,%d}\n",
									&i,
									&config[0],
									&config[1],
									&config[2],
									&config[3]);
							if (ret == 5) {
								if (i >= 0 && i < cfg->num_t8_config) {
									cfg->t8_cfg[i].atchcalst = (u8)config[0];
									cfg->t8_cfg[i].atchcalsthr = (u8)config[1];
									cfg->t8_cfg[i].atchfrccalthr = (u8)config[2];
									cfg->t8_cfg[i].atchfrccalratio = (s8)config[3];
									dev_info(dev, "[mxt]OK\n");
								} else {
									dev_err(dev, "[mxt]Invalid t8 type %d\n", i);
									return -EINVAL;
								}
							} else {
								dev_err(dev, "[mxt]Invalid t%d : %s , %d\n",object, buf + offset,ret);
								return -EINVAL;
							}
							break;
						case 9:
						case 100:
							ret = sscanf(buf + offset, "(%d): {%d,%d,%d,%d,%d,%d,%d}\n",
									&i,
									&config[0],
									&config[1],
									&config[2],
									&config[3],
								&config[4],
								&config[5],
								&config[6]);
							if (ret == 8){
								if (i >=0 && i < cfg->num_t9_t100_config){
									cfg->t9_t100_cfg[i].threshold = (u8)config[0];
									cfg->t9_t100_cfg[i].hysterisis = (u8)config[1];
									cfg->t9_t100_cfg[i].internal_threshold = (u8)config[2];
									cfg->t9_t100_cfg[i].internal_hysterisis = (u8)config[3];
									cfg->t9_t100_cfg[i].merge_threshold = (u8)config[4];
									cfg->t9_t100_cfg[i].merge_hysterisis = (s8)config[5];
									cfg->t9_t100_cfg[i].dualx_threshold = (s8)config[6];
									dev_info(dev, "[mxt]OK\n");
								}else{
									dev_err(dev, "[mxt]Invalid t%d type %d\n", object, i);
									return -EINVAL;
								}
							}else{
								dev_err(dev, "[mxt]Invalid t%d %s ret %d\n",object, buf + offset, ret);
								return -EINVAL;
							}
							break;
						case 55:
							ret = sscanf(buf + offset, "(%d): {0x%x}\n",
									&i,
									&config[0]);
							if (ret == 2) {
								if (i >=0 && i < cfg->num_t55_config) {
									cfg->t55_cfg[i].ctrl= (u8)config[0];
									dev_info(dev, "[mxt]OK\n");
								} else {
									dev_err(dev, "[mxt]Invalid t%d type %d\n", object, i);
									return -EINVAL;
								}
							} else{
								dev_err(dev, "[mxt]Invalid t%d : %s ret %d\n",object, buf + offset, ret);
								return -EINVAL;
							}
							break;
						case 61:
							ret = sscanf(buf + offset, "(%d): {0x%x,0x%x,0x%x,%d}\n",
									&i,
									&config[0],
									&config[1],
									&config[2],
									&config[3]);
							if (ret == 5) {
								if (i >=0 && i < cfg->num_t61_config) {
									cfg->t61_cfg[i].ctrl = (u8)config[0];
									cfg->t61_cfg[i].cmd = (u8)config[1];
									cfg->t61_cfg[i].mode = (u8)config[2];
									cfg->t61_cfg[i].period = (s8)config[3];
									dev_info(dev, "[mxt]OK\n");
								} else {
									dev_err(dev, "[mxt]Invalid t%d type %d\n", object, i);
									return -EINVAL;
								}
							} else {
								dev_err(dev, "[mxt]Invalid t%d : %s ret %d\n",object, buf + offset, ret);
								return -EINVAL;
							}
							break;
						case 65:
							ret = sscanf(buf + offset, "(%d): {0x%x,%d,%d}\n",
								&i,
								&config[0],
								&config[1],
								&config[2]);
							if (ret == 4){
								if (i >=0 && i < cfg->num_t65_config){
									cfg->t65_cfg[i].ctrl = (u8)config[0];
									cfg->t65_cfg[i].grad_thr = (u8)config[1];
									cfg->t65_cfg[i].lpfilter = (u8)config[2];
									dev_info(dev, "[mxt]OK\n");
								} else {
									dev_err(dev, "[mxt]Invalid t%d type %d\n", object, i);
									return -EINVAL;
								}
							} else {
								dev_err(dev, "[mxt]Invalid t%d : %s ret %d\n",object, buf + offset, ret);
								return -EINVAL;
							}
							break;
						case 80:
							ret = sscanf(buf + offset, "(%d): {0x%x,%u,%u,%u,%u}\n",
									&i,
									&config[0],
									&config[1],
									&config[2],
									&config[3],
									&config[4]);
							if (ret == 6) {
								if (i >=0 && i < cfg->num_t80_config) {
									cfg->t80_cfg[i].ctrl = (u8)config[0];
									cfg->t80_cfg[i].comp_gain= (u8)config[1];
									cfg->t80_cfg[i].target_delta = (u8)config[2];
									cfg->t80_cfg[i].compthr= (u8)config[3];
									cfg->t80_cfg[i].atchthr = (u8)config[4];
									dev_info(dev, "[mxt]OK\n");
								} else {
									dev_err(dev, "[mxt]Invalid t%d type %d\n", object, i);
									return -EINVAL;
								}
							} else {
								dev_err(dev, "[mxt]Invalid t%d : %s ret %d\n",object, buf + offset, ret);
								return -EINVAL;
							}
							break;
						default:
							dev_err(dev, "[mxt]Invalid object %d, %s\n",object, buf + offset);
							return -EINVAL;
					}
				} else if (sscanf(buf + offset, "status: Flag=0x%lx\n",
							&obs->flag) > 0) {
					dev_info(dev, "[mxt] OK\n");
				}else if (sscanf(buf + offset, "enable %x\n",
					&config[0]) == 1){
					config[0] = ((~config[0]) << PL_STATUS_FLAG_HIGH_MASK_SHIFT) & PL_STATUS_FLAG_PAUSE_MASK;
					set_and_clr_flag(config[0],PL_STATUS_FLAG_PAUSE_MASK,&obs->flag);
					dev_info(dev, "[mxt]OK(Flag = 0x%08lx)\n",obs->flag);
				} else {
					dev_err(dev, "Unknow parse pl command: %s count %d, object %d, ofs %d, ret %d\n",buf,count,object,ofs,ret);
				}
			} else if (strncmp(name, "cal", 3) == 0) {
				dev_info(dev, "cmd = 'cal': %s",buf + 4);
				if (pl->cal->store)
					pl->cal->store(pl->cal, buf + 4, count - 4);
			} else if (strncmp(name, "ac", 2) == 0) {
				dev_info(dev, "cmd = 'ac': %s",buf + 3);
				if (pl->ac->store)
					pl->ac->store(pl->ac, buf + 3, count - 3);
			}else if (strncmp(name, "pi", 2) == 0){
				dev_info(dev, "cmd = 'pi': %s",buf + 3);
				if (pl->pi->store)
					pl->pi->store(pl->pi, buf + 3, count - 3);
			} else {
				dev_err(dev, "Unknow command: %s\n",buf);
				return -EINVAL;
			}
		} else{
			dev_err(dev, "Unknow parameter, ret %d\n",ret);
		}

		if (pl->active_thread)
		   pl->active_thread(pl->dev,MXT_EVENT_EXTERN);
		return count;
	} else {
		dev_dbg(dev, "Unknow count: %d\n",count);
		return -EINVAL;
	}
}

static ssize_t mxt_plugin_tag_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct mxt_data *data = dev_get_drvdata(dev);
	struct plug_interface *pl = &data->plug_in;
	int ret = 0;

	if (!pl->inited)
		return -ENODEV;

	dev_info(dev, "[mxt]Plug tag :\n");

	ret = scnprintf(buf, PAGE_SIZE, "%u.%u.%u.%u.%u.%u.%u.%u\n",
				pl->init_cfg.t38.data[0],
				pl->init_cfg.t38.data[1],
				pl->init_cfg.t38.data[2],
				pl->init_cfg.t38.data[3],
				pl->init_cfg.t38.data[4],
				pl->init_cfg.t38.data[5],
				pl->init_cfg.t38.data[6],
				pl->init_cfg.t38.data[7]);

	dev_info(dev, "[mxt] %s\n", buf);

	return ret;
}


