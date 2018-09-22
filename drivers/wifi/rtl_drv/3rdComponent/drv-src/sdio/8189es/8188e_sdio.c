/*
 *  SDIO core routines
 *
 *  $Id: 8188e_sdio.c,v 1.27.2.31 2010/12/31 08:37:43 family Exp $
 *
 *  Copyright (c) 2009 Realtek Semiconductor Corp.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#define _8188E_SDIO_C_

#ifdef __KERNEL__
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#endif

#include "8192cd.h"
#include "8192cd_headers.h"
#include "8192cd_debug.h"


#define SDIO_ERR_VAL8	0xEA
#define SDIO_ERR_VAL16	0xEAEA
#define SDIO_ERR_VAL32	0xEAEAEAEA

const u32 reg_freepage_thres[SDIO_TX_FREE_PG_QUEUE] = {
	REG_88E_TXDMA_TH+1, REG_88E_TXDMA_TH+3, REG_88E_LQ_TH+1, 0
};


u8 sd_f0_read8(struct rtl8192cd_priv *priv, u32 addr, s32 *err)
{
	u8 v;
	struct sdio_func *func;
	
	func = priv->pshare->psdio_func;

	sdio_claim_host(func);
	v = sdio_f0_readb(func, addr, err);
	sdio_release_host(func);
	if (err && *err)
		printk(KERN_ERR "%s: FAIL!(%d) addr=0x%05x\n", __func__, *err, addr);

	return v;
}

void sd_f0_write8(struct rtl8192cd_priv *priv, u32 addr, u8 v, s32 *err)
{
	struct sdio_func *func;

	func = priv->pshare->psdio_func;

	sdio_claim_host(func);
	sdio_f0_writeb(func, v, addr, err);
	sdio_release_host(func);
	if (err && *err)
		printk(KERN_ERR "%s: FAIL!(%d) addr=0x%05x val=0x%02x\n", __func__, *err, addr, v);
}

/*
 * Return:
 *	0		Success
 *	others	Fail
 */
s32 _sd_cmd52_read(struct rtl8192cd_priv *priv, u32 addr, u32 cnt, u8 *pdata)
{
	int err, i;
	struct sdio_func *func;

	err = 0;
	func = priv->pshare->psdio_func;

	for (i = 0; i < cnt; i++) {
		pdata[i] = sdio_readb(func, addr+i, &err);
		if (err) {
			printk(KERN_ERR "%s: FAIL!(%d) addr=0x%05x\n", __func__, err, addr);
			break;
		}
	}

	return err;
}

/*
 * Return:
 *	0		Success
 *	others	Fail
 */
s32 sd_cmd52_read(struct rtl8192cd_priv *priv, u32 addr, u32 cnt, u8 *pdata)
{
	int err;
	struct sdio_func *func;

	err = 0;
	func = priv->pshare->psdio_func;

	sdio_claim_host(func);
	err = _sd_cmd52_read(priv, addr, cnt, pdata);
	sdio_release_host(func);

	return err;
}

/*
 * Return:
 *	0		Success
 *	others	Fail
 */
s32 _sd_cmd52_write(struct rtl8192cd_priv *priv, u32 addr, u32 cnt, u8 *pdata)
{
	int err, i;
	struct sdio_func *func;

	err = 0;
	func = priv->pshare->psdio_func;

	for (i = 0; i < cnt; i++) {
		sdio_writeb(func, pdata[i], addr+i, &err);
		if (err) {
			printk(KERN_ERR "%s: FAIL!(%d) addr=0x%05x val=0x%02x\n", __func__, err, addr, pdata[i]);
			break;
		}
	}

	return err;
}

/*
 * Return:
 *	0		Success
 *	others	Fail
 */
s32 sd_cmd52_write(struct rtl8192cd_priv *priv, u32 addr, u32 cnt, u8 *pdata)
{
	int err;
	struct sdio_func *func;

	err = 0;
	func = priv->pshare->psdio_func;

	sdio_claim_host(func);
	err = _sd_cmd52_write(priv, addr, cnt, pdata);
	sdio_release_host(func);

	return err;
}

u8 _sd_read8(struct rtl8192cd_priv *priv, u32 addr, s32 *err)
{
	u8 v;
	struct sdio_func *func;

	func = priv->pshare->psdio_func;

	//sdio_claim_host(func);
	v = sdio_readb(func, addr, err);
	//sdio_release_host(func);
	if (err && *err)
		printk(KERN_ERR "%s: FAIL!(%d) addr=0x%05x\n", __func__, *err, addr);

	return v;
}

u8 sd_read8(struct rtl8192cd_priv *priv, u32 addr, s32 *err)
{
	u8 v;
	struct sdio_func *func;

	func = priv->pshare->psdio_func;

	sdio_claim_host(func);
	v = sdio_readb(func, addr, err);
	sdio_release_host(func);
	if (err && *err)
		printk(KERN_ERR "%s: FAIL!(%d) addr=0x%05x\n", __func__, *err, addr);

	return v;
}

u16 sd_read16(struct rtl8192cd_priv *priv, u32 addr, s32 *err)
{
	u16 v;
	struct sdio_func *func;

	func = priv->pshare->psdio_func;

	sdio_claim_host(func);
	v = sdio_readw(func, addr, err);
	sdio_release_host(func);
	if (err && *err)
		printk(KERN_ERR "%s: FAIL!(%d) addr=0x%05x\n", __func__, *err, addr);

	return  v;
}

u32 _sd_read32(struct rtl8192cd_priv *priv, u32 addr, s32 *err)
{
	u32 v;
	struct sdio_func *func;

	func = priv->pshare->psdio_func;

	//sdio_claim_host(func);
	v = sdio_readl(func, addr, err);
	//sdio_release_host(func);
	if (err && *err)
		printk(KERN_ERR "%s: FAIL!(%d) addr=0x%05x\n", __func__, *err, addr);

	return  v;
}

u32 sd_read32(struct rtl8192cd_priv *priv, u32 addr, s32 *err)
{
	u32 v;
	struct sdio_func *func;

	func = priv->pshare->psdio_func;

	sdio_claim_host(func);
	v = sdio_readl(func, addr, err);
	sdio_release_host(func);
	if (err && *err)
		printk(KERN_ERR "%s: FAIL!(%d) addr=0x%05x\n", __func__, *err, addr);

	return  v;
}

void sd_write8(struct rtl8192cd_priv *priv, u32 addr, u8 v, s32 *err)
{
	struct sdio_func *func;

	func = priv->pshare->psdio_func;

	sdio_claim_host(func);
	sdio_writeb(func, v, addr, err);
	sdio_release_host(func);
	if (err && *err)
		printk(KERN_ERR "%s: FAIL!(%d) addr=0x%05x val=0x%02x\n", __func__, *err, addr, v);
}

void sd_write16(struct rtl8192cd_priv *priv, u32 addr, u16 v, s32 *err)
{
	struct sdio_func *func;

	func = priv->pshare->psdio_func;

	sdio_claim_host(func);
	sdio_writew(func, v, addr, err);
	sdio_release_host(func);
	if (err && *err)
		printk(KERN_ERR "%s: FAIL!(%d) addr=0x%05x val=0x%04x\n", __func__, *err, addr, v);
}

void _sd_write32(struct rtl8192cd_priv *priv, u32 addr, u32 v, s32 *err)
{
	struct sdio_func *func;

	func = priv->pshare->psdio_func;

	//sdio_claim_host(func);
	sdio_writel(func, v, addr, err);
	//sdio_release_host(func);
	if (err && *err)
		printk(KERN_ERR "%s: FAIL!(%d) addr=0x%05x val=0x%08x\n", __func__, *err, addr, v);
}

void sd_write32(struct rtl8192cd_priv *priv, u32 addr, u32 v, s32 *err)
{
	struct sdio_func *func;

	func = priv->pshare->psdio_func;

	sdio_claim_host(func);
	sdio_writel(func, v, addr, err);
	sdio_release_host(func);
	if (err && *err)
		printk(KERN_ERR "%s: FAIL!(%d) addr=0x%05x val=0x%08x\n", __func__, *err, addr, v);
}

/*
 * Use CMD53 to read data from SDIO device.
 * This function MUST be called after sdio_claim_host() or
 * in SDIO ISR(host had been claimed).
 *
 * Parameters:
 *	psdio	pointer of SDIO_DATA
 *	addr	address to read
 *	cnt		amount to read
 *	pdata	pointer to put data, this should be a "DMA:able scratch buffer"!
 *
 * Return:
 *	0		Success
 *	others	Fail
 */
s32 _sd_read(struct rtl8192cd_priv *priv, u32 addr, u32 cnt, void *pdata)
{
	int err;
	struct sdio_func *func;

	func = priv->pshare->psdio_func;

	if (unlikely((cnt==1) || (cnt==2)))
	{
		int i;
		u8 *pbuf = (u8*)pdata;

		for (i = 0; i < cnt; i++)
		{
			*(pbuf+i) = sdio_readb(func, addr+i, &err);

			if (err) {
				printk(KERN_ERR "%s: FAIL!(%d) addr=0x%05x\n", __func__, err, addr);
				break;
			}
		}
		return err;
	}

	err = sdio_memcpy_fromio(func, pdata, addr, cnt);
	if (err) {
		printk(KERN_ERR "%s: FAIL(%d)! ADDR=%#x Size=%d\n", __func__, err, addr, cnt);
	}

	return err;
}

/*
 * Use CMD53 to read data from SDIO device.
 *
 * Parameters:
 *	psdio	pointer of SDIO_DATA
 *	addr	address to read
 *	cnt		amount to read
 *	pdata	pointer to put data, this should be a "DMA:able scratch buffer"!
 *
 * Return:
 *	0		Success
 *	others	Fail
 */
s32 sd_read(struct rtl8192cd_priv *priv, u32 addr, u32 cnt, void *pdata)
{
	s32 err;
	struct sdio_func *func;

	func = priv->pshare->psdio_func;

	sdio_claim_host(func);
	err = _sd_read(priv, addr, cnt, pdata);
	sdio_release_host(func);

	return err;
}

/*
 * Use CMD53 to write data to SDIO device.
 * This function MUST be called after sdio_claim_host() or
 * in SDIO ISR(host had been claimed).
 *
 * Parameters:
 *	psdio	pointer of SDIO_DATA
 *	addr	address to write
 *	cnt		amount to write
 *	pdata	data pointer, this should be a "DMA:able scratch buffer"!
 *
 * Return:
 *	0		Success
 *	others	Fail
 */
s32 _sd_write(struct rtl8192cd_priv *priv, u32 addr, u32 cnt, void *pdata)
{
	int err;
	struct sdio_func *func;
	u32 size;

	func = priv->pshare->psdio_func;
//	size = sdio_align_size(func, cnt);

	if (unlikely((cnt==1) || (cnt==2)))
	{
		int i;
		u8 *pbuf = (u8*)pdata;

		for (i = 0; i < cnt; i++)
		{
			sdio_writeb(func, *(pbuf+i), addr+i, &err);
			if (err) {
				printk(KERN_ERR "%s: FAIL!(%d) addr=0x%05x val=0x%02x\n", __func__, err, addr, *(pbuf+i));
				break;
			}
		}

		return err;
	}

	size = cnt;
	err = sdio_memcpy_toio(func, addr, pdata, size);
	if (err) {
		printk(KERN_ERR "%s: FAIL(%d)! ADDR=%#x Size=%d(%d)\n", __func__, err, addr, cnt, size);
	}
	
	return err;
}

/*
 * Use CMD53 to write data to SDIO device.
 *
 * Parameters:
 *  psdio	pointer of SDIO_DATA
 *  addr	address to write
 *  cnt		amount to write
 *  pdata	data pointer, this should be a "DMA:able scratch buffer"!
 *
 * Return:
 *  0		Success
 *  others	Fail
 */
s32 sd_write(struct rtl8192cd_priv *priv, u32 addr, u32 cnt, void *pdata)
{
	s32 err;
	struct sdio_func *func;

	func = priv->pshare->psdio_func;

	sdio_claim_host(func);
	err = _sd_write(priv, addr, cnt, pdata);
	sdio_release_host(func);

	return err;
}

//
// Description:
//	The following mapping is for SDIO host local register space.
//
// Creadted by Roger, 2011.01.31.
//
static void HalSdioGetCmdAddr8723ASdio(struct rtl8192cd_priv *priv, u8 DeviceID, u32 Addr, u32* pCmdAddr)
{
	switch (DeviceID)
	{
		case SDIO_LOCAL_DEVICE_ID:
			*pCmdAddr = ((SDIO_LOCAL_DEVICE_ID << 13) | (Addr & SDIO_LOCAL_MSK));
			break;

		case WLAN_IOREG_DEVICE_ID:
			*pCmdAddr = ((WLAN_IOREG_DEVICE_ID << 13) | (Addr & WLAN_IOREG_MSK));
			break;

		case WLAN_TX_HIQ_DEVICE_ID:
			*pCmdAddr = ((WLAN_TX_HIQ_DEVICE_ID << 13) | (Addr & WLAN_FIFO_MSK));
			break;

		case WLAN_TX_MIQ_DEVICE_ID:
			*pCmdAddr = ((WLAN_TX_MIQ_DEVICE_ID << 13) | (Addr & WLAN_FIFO_MSK));
			break;

		case WLAN_TX_LOQ_DEVICE_ID:
			*pCmdAddr = ((WLAN_TX_LOQ_DEVICE_ID << 13) | (Addr & WLAN_FIFO_MSK));
			break;

		case WLAN_RX0FF_DEVICE_ID:
			*pCmdAddr = ((WLAN_RX0FF_DEVICE_ID << 13) | (Addr & WLAN_RX0FF_MSK));
			break;

		default:
			break;
	}
}

static u8 get_deviceid(u32 addr)
{
	u32 baseAddr;
	u8 devideId;

	baseAddr = addr & 0xffff0000;
	
	switch (baseAddr) {
	case SDIO_LOCAL_BASE:
		devideId = SDIO_LOCAL_DEVICE_ID;
		break;

	case WLAN_IOREG_BASE:
		devideId = WLAN_IOREG_DEVICE_ID;
		break;

//	case FIRMWARE_FIFO_BASE:
//		devideId = SDIO_FIRMWARE_FIFO;
//		break;

	case TX_HIQ_BASE:
		devideId = WLAN_TX_HIQ_DEVICE_ID;
		break;

	case TX_MIQ_BASE:
		devideId = WLAN_TX_MIQ_DEVICE_ID;
		break;

	case TX_LOQ_BASE:
		devideId = WLAN_TX_LOQ_DEVICE_ID;
		break;

	case RX_RX0FF_BASE:
		devideId = WLAN_RX0FF_DEVICE_ID;
		break;

	default:
//		devideId = (u8)((addr >> 13) & 0xF);
		devideId = WLAN_IOREG_DEVICE_ID;
		break;
	}

	return devideId;
}

/*
 * Ref:
 *	HalSdioGetCmdAddr8723ASdio()
 */
static u32 _cvrt2ftaddr(const u32 addr, u8 *pdeviceId, u16 *poffset)
{
	u8 deviceId;
	u16 offset;
	u32 ftaddr;


	deviceId = get_deviceid(addr);
	offset = 0;

	switch (deviceId)
	{
		case SDIO_LOCAL_DEVICE_ID:
			offset = addr & SDIO_LOCAL_MSK;
			break;

		case WLAN_TX_HIQ_DEVICE_ID:
		case WLAN_TX_MIQ_DEVICE_ID:
		case WLAN_TX_LOQ_DEVICE_ID:
			offset = addr & WLAN_FIFO_MSK;
			break;

		case WLAN_RX0FF_DEVICE_ID:
			offset = addr & WLAN_RX0FF_MSK;
			break;

		case WLAN_IOREG_DEVICE_ID:
		default:
			deviceId = WLAN_IOREG_DEVICE_ID;
			offset = addr & WLAN_IOREG_MSK;
			break;
	}
	ftaddr = (deviceId << 13) | offset;

	if (pdeviceId) *pdeviceId = deviceId;
	if (poffset) *poffset = offset;

	return ftaddr;
}

u8 _sdio_read8(struct rtl8192cd_priv *priv, u32 addr)
{
	u32 ftaddr;
	u8 val;
	
	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
	val = _sd_read8(priv, ftaddr, NULL);
	
	return val;
}

u8 sdio_read8(struct rtl8192cd_priv *priv, u32 addr)
{
	u32 ftaddr;
	u8 val;

	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
	val = sd_read8(priv, ftaddr, NULL);

	return val;
}

u16 sdio_read16(struct rtl8192cd_priv *priv, u32 addr)
{
	u32 ftaddr;
	u16 val;

	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
	sd_cmd52_read(priv, ftaddr, 2, (u8*)&val);
	val = le16_to_cpu(val);

	return val;
}

u32 _sdio_read32(struct rtl8192cd_priv *priv, u32 addr)
{
	u8 deviceId;
	u16 offset;
	u32 ftaddr;
	u8 shift;
	u32 val;
	s32 err;

	ftaddr = _cvrt2ftaddr(addr, &deviceId, &offset);

	if (((deviceId == WLAN_IOREG_DEVICE_ID) && (offset < 0x100))
		|| (FALSE == GET_HAL_INTF_DATA(priv)->bMacPwrCtrlOn)
#ifdef CONFIG_LPS_LCLK
		|| (TRUE == padapter->pwrctrlpriv.bFwCurrentInPSMode)
#endif
		)
        {
		err = _sd_cmd52_read(priv, ftaddr, 4, (u8*)&val);
#ifdef SDIO_DEBUG_IO
		if (err) {
			printk(KERN_ERR "%s: Mac Power off, Read FAIL(%d)! addr=0x%x\n", __func__, err, addr);
			return SDIO_ERR_VAL32;
		}
#endif
		val = le32_to_cpu(val);
		return val;
	}

	// 4 bytes alignment
	shift = ftaddr & 0x3;
	if (shift == 0) {
		val = _sd_read32(priv, ftaddr, NULL);
	} else {
		u8 tmpbuf[8];

		ftaddr &= ~0x3;
		err = _sd_read(priv, ftaddr, 8, tmpbuf);
		memcpy(&val, tmpbuf+shift, 4);
		val = le32_to_cpu(val);
	}

	return val;
}

u32 sdio_read32(struct rtl8192cd_priv *priv, u32 addr)
{
	u8 deviceId;
	u16 offset;
	u32 ftaddr;
	u8 shift;
	u32 val;
	s32 err;
	
	ftaddr = _cvrt2ftaddr(addr, &deviceId, &offset);

	if (((deviceId == WLAN_IOREG_DEVICE_ID) && (offset < 0x100))
		|| (FALSE == GET_HAL_INTF_DATA(priv)->bMacPwrCtrlOn)
#ifdef CONFIG_LPS_LCLK
		|| (TRUE == padapter->pwrctrlpriv.bFwCurrentInPSMode)
#endif
		)
	{
		err = sd_cmd52_read(priv, ftaddr, 4, (u8*)&val);
#ifdef SDIO_DEBUG_IO
		if (err) {
			printk(KERN_ERR "%s: Mac Power off, Read FAIL(%d)! addr=0x%x\n", __func__, err, addr);
			return SDIO_ERR_VAL32;
		}
#endif
		val = le32_to_cpu(val);
		return val;
	}

	// 4 bytes alignment
	shift = ftaddr & 0x3;
	if (shift == 0) {
		val = sd_read32(priv, ftaddr, NULL);
	} else {
		u8 tmpbuf[8];

		ftaddr &= ~0x3;
		err = sd_read(priv, ftaddr, 8, tmpbuf);
		memcpy(&val, tmpbuf+shift, 4);
		val = le32_to_cpu(val);
	}

	return val;
}

s32 sdio_readN(struct rtl8192cd_priv *priv, u32 addr, u32 cnt, u8 *pbuf)
{
	u8 deviceId;
	u16 offset;
	u32 ftaddr;
	u8 shift;
	s32 err;
	
	err = 0;
	ftaddr = _cvrt2ftaddr(addr, &deviceId, &offset);

	if (((deviceId == WLAN_IOREG_DEVICE_ID) && (offset < 0x100))
		|| (FALSE == GET_HAL_INTF_DATA(priv)->bMacPwrCtrlOn)
#ifdef CONFIG_LPS_LCLK
		|| (TRUE == padapter->pwrctrlpriv.bFwCurrentInPSMode)
#endif
		)
	{
		err = sd_cmd52_read(priv, ftaddr, cnt, pbuf);
		return err;
	}

	// 4 bytes alignment
	shift = ftaddr & 0x3;
	if (shift == 0) {
		err = sd_read(priv, ftaddr, cnt, pbuf);
	} else {
		u8 *ptmpbuf;
		u32 n;

		ftaddr &= ~0x3;
		n = cnt + shift;
		ptmpbuf = rtw_malloc(n);
		if (NULL == ptmpbuf) return -ENOMEM;
		
		err = sd_read(priv, ftaddr, n, ptmpbuf);
		if (!err)
			memcpy(pbuf, ptmpbuf+shift, cnt);
		
		rtw_mfree(ptmpbuf, n);
	}

	return err;
}

s32 sdio_write8(struct rtl8192cd_priv *priv, u32 addr, u8 val)
{
	u32 ftaddr;
	s32 err;

	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
	sd_write8(priv, ftaddr, val, &err);

	return err;
}

s32 sdio_write16(struct rtl8192cd_priv *priv, u32 addr, u16 val)
{
	u32 ftaddr;
	s32 err;

	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
	val = cpu_to_le16(val);
	err = sd_cmd52_write(priv, ftaddr, 2, (u8*)&val);

	return err;
}

s32 _sdio_write32(struct rtl8192cd_priv *priv, u32 addr, u32 val)
{
	u8 deviceId;
	u16 offset;
	u32 ftaddr;
	u8 shift;
	s32 err;
	
	err = 0;
	ftaddr = _cvrt2ftaddr(addr, &deviceId, &offset);

	if (((deviceId == WLAN_IOREG_DEVICE_ID) && (offset < 0x100))
		|| (FALSE == GET_HAL_INTF_DATA(priv)->bMacPwrCtrlOn)
#ifdef CONFIG_LPS_LCLK
		|| (TRUE == padapter->pwrctrlpriv.bFwCurrentInPSMode)
#endif
		)
	{
		val = cpu_to_le32(val);
		err = _sd_cmd52_write(priv, ftaddr, 4, (u8*)&val);
		return err;
	}

	// 4 bytes alignment
	shift = ftaddr & 0x3;
#if 1
	if (shift == 0)
	{
		_sd_write32(priv, ftaddr, val, &err);
	}
	else
	{
		val = cpu_to_le32(val);
		err = _sd_cmd52_write(priv, ftaddr, 4, (u8*)&val);
	}
#else
	if (shift == 0) {
		sd_write32(priv, ftaddr, val, &err);
	} else {
		u8 *ptmpbuf;

		ptmpbuf = (u8*)rtw_malloc(8);
		if (NULL == ptmpbuf) return -ENOMEM;

		ftaddr &= ~0x3;
		err = sd_read(priv, ftaddr, 8, ptmpbuf);
		if (err) {
			_rtw_mfree(ptmpbuf, 8);
			return err;
		}
		val = cpu_to_le32(val);
		memcpy(ptmpbuf+shift, &val, 4);
		err = sd_write(priv, ftaddr, 8, ptmpbuf);

		rtw_mfree(ptmpbuf, 8);
	}
#endif
	
	return err;
}

s32 sdio_write32(struct rtl8192cd_priv *priv, u32 addr, u32 val)
{
	u8 deviceId;
	u16 offset;
	u32 ftaddr;
	u8 shift;
	s32 err;
	
	err = 0;
	ftaddr = _cvrt2ftaddr(addr, &deviceId, &offset);

	if (((deviceId == WLAN_IOREG_DEVICE_ID) && (offset < 0x100))
		|| (FALSE == GET_HAL_INTF_DATA(priv)->bMacPwrCtrlOn)
#ifdef CONFIG_LPS_LCLK
		|| (TRUE == padapter->pwrctrlpriv.bFwCurrentInPSMode)
#endif
		)
	{
		val = cpu_to_le32(val);
		err = sd_cmd52_write(priv, ftaddr, 4, (u8*)&val);
		return err;
	}

	// 4 bytes alignment
	shift = ftaddr & 0x3;
#if 1
	if (shift == 0)
	{
		sd_write32(priv, ftaddr, val, &err);
	}
	else
	{
		val = cpu_to_le32(val);
		err = sd_cmd52_write(priv, ftaddr, 4, (u8*)&val);
	}
#else
	if (shift == 0) {
		sd_write32(priv, ftaddr, val, &err);
	} else {
		u8 *ptmpbuf;

		ptmpbuf = (u8*)rtw_malloc(8);
		if (NULL == ptmpbuf) return -ENOMEM;

		ftaddr &= ~0x3;
		err = sd_read(priv, ftaddr, 8, ptmpbuf);
		if (err) {
			rtw_mfree(ptmpbuf, 8);
			return err;
		}
		val = cpu_to_le32(val);
		memcpy(ptmpbuf+shift, &val, 4);
		err = sd_write(priv, ftaddr, 8, ptmpbuf);

		rtw_mfree(ptmpbuf, 8);
	}
#endif

	return err;
}

s32 sdio_writeN(struct rtl8192cd_priv *priv, u32 addr, u32 cnt, u8* pbuf)
{
	u8 deviceId;
	u16 offset;
	u32 ftaddr;
	u8 shift;
	s32 err;
	
	err = 0;
	ftaddr = _cvrt2ftaddr(addr, &deviceId, &offset);

	if (((deviceId == WLAN_IOREG_DEVICE_ID) && (offset < 0x100))
		|| (FALSE == GET_HAL_INTF_DATA(priv)->bMacPwrCtrlOn)
#ifdef CONFIG_LPS_LCLK
		|| (TRUE == padapter->pwrctrlpriv.bFwCurrentInPSMode)
#endif
		)
	{
		err = sd_cmd52_write(priv, ftaddr, cnt, pbuf);
		return err;
	}

	shift = ftaddr & 0x3;
	if (shift == 0) {
		err = sd_write(priv, ftaddr, cnt, pbuf);
	} else {
		u8 *ptmpbuf;
		u32 n;

		ftaddr &= ~0x3;
		n = cnt + shift;
		ptmpbuf = rtw_malloc(n);
		if (NULL == ptmpbuf) return -ENOMEM;
		err = sd_read(priv, ftaddr, 4, ptmpbuf);
		if (err) {
			rtw_mfree(ptmpbuf, n);
			return err;
		}
		memcpy(ptmpbuf+shift, pbuf, cnt);
		err = sd_write(priv, ftaddr, n, ptmpbuf);
		rtw_mfree(ptmpbuf, n);
	}

	return err;
}

/*
 * Description:
 *	Read from RX FIFO
 *	Round read size to block size,
 *	and make sure data transfer will be done in one command.
 *
 * Parameters:
 *	pintfhdl	a pointer of intf_hdl
 *	addr		port ID
 *	cnt			size to read
 *	rmem		address to put data
 *
 * Return:
 *	= 0		Success
 *	!= 0		Fail
 */
u32 sdio_read_port(struct rtl8192cd_priv *priv, u32 addr, u32 cnt, u8 *mem)
{
	struct priv_shared_info *pshare = priv->pshare;
	HAL_INTF_DATA_TYPE *pHalData = GET_HAL_INTF_DATA(priv);
	s32 err;

	HalSdioGetCmdAddr8723ASdio(priv, addr, pHalData->SdioRxFIFOCnt++, &addr);


	cnt = _RND4(cnt);
	if (cnt > pshare->block_transfer_len)
		cnt = _RND(cnt, pshare->block_transfer_len);

//	cnt = sdio_align_size(cnt);

	err = _sd_read(priv, addr, cnt, mem);
	//err = sd_read(priv, addr, cnt, mem);
	
	return err;
}

/*
 * Description:
 *	Write to TX FIFO
 *	Align write size block size,
 *	and make sure data could be written in one command.
 *
 * Parameters:
 *	pintfhdl	a pointer of intf_hdl
 *	addr		port ID
 *	cnt			size to write
 *	wmem		data pointer to write
 *
 * Return:
 *	= 0		Success
 *	!= 0		Fail
 */
u32 sdio_write_port(struct rtl8192cd_priv *priv, u32 addr, u32 cnt, u8 *mem)
{
	s32 err;
	struct priv_shared_info *pshare = priv->pshare;
	struct xmit_buf *pxmitbuf = (struct xmit_buf *)mem;
#ifdef CONFIG_XMITBUF_TXAGG_ADV
	const int q_num = pxmitbuf->q_num;
#endif

	cnt = _RND4(cnt);
	HalSdioGetCmdAddr8723ASdio(priv, addr, cnt >> 2, &addr);

	if (cnt > pshare->block_transfer_len)
		cnt = _RND(cnt, pshare->block_transfer_len);
//	cnt = sdio_align_size(cnt);

	err = sd_write(priv, addr, cnt, pxmitbuf->pkt_data);
	pxmitbuf->status = err;

//	rtw_sctx_done_err(&xmitbuf->sctx,
//		err ? RTW_SCTX_DONE_WRITE_PORT_ERR : RTW_SCTX_DONE_SUCCESS);

	if (err) {
		printk("%s, error=%d\n", __func__, err);
	}
	
#ifdef CONFIG_XMITBUF_TXAGG_ADV
    if ((q_num >= BK_QUEUE) && (q_num <= VO_QUEUE))
    {
		pshare->low_traffic_xmit_stats[q_num] += pxmitbuf->agg_num;
	}
#endif
	
	return err;
}

/*
 * Todo: align address to 4 bytes.
 */
s32 _sdio_local_read(struct rtl8192cd_priv *priv, u32 addr, u32 cnt, u8 *pbuf)
{
	s32 err;
	u8 *ptmpbuf;
	u32 n;

	HalSdioGetCmdAddr8723ASdio(priv, SDIO_LOCAL_DEVICE_ID, addr, &addr);

	if ((FALSE == GET_HAL_INTF_DATA(priv)->bMacPwrCtrlOn)
#ifdef CONFIG_LPS_LCLK
//		|| (_TRUE == padapter->pwrctrlpriv.bFwCurrentInPSMode)
#endif
		)
	{
		err = _sd_cmd52_read(priv, addr, cnt, pbuf);
		return err;
	}

        n = _RND4(cnt);
	ptmpbuf = (u8*)rtw_malloc(n);
	if (NULL == ptmpbuf)
		return -ENOMEM;

	err = _sd_read(priv, addr, n, ptmpbuf);
	if (!err)
		memcpy(pbuf, ptmpbuf, cnt);

	rtw_mfree(ptmpbuf, n);

	return err;
}

/*
 * Todo: align address to 4 bytes.
 */
s32 sdio_local_read(struct rtl8192cd_priv *priv, u32 addr, u32 cnt, u8 *pbuf)
{
	s32 err;
	u8 *ptmpbuf;
	u32 n;

	HalSdioGetCmdAddr8723ASdio(priv, SDIO_LOCAL_DEVICE_ID, addr, &addr);

	if ((FALSE == GET_HAL_INTF_DATA(priv)->bMacPwrCtrlOn)
#ifdef CONFIG_LPS_LCLK
		|| (TRUE == padapter->pwrctrlpriv.bFwCurrentInPSMode)
#endif
		)
	{
		err = sd_cmd52_read(priv, addr, cnt, pbuf);
		return err;
	}

        n = _RND4(cnt);
	ptmpbuf = (u8*)rtw_malloc(n);
	if (NULL == ptmpbuf)
		return -ENOMEM;

	err = sd_read(priv, addr, n, ptmpbuf);
	if (!err)
		memcpy(pbuf, ptmpbuf, cnt);

	rtw_mfree(ptmpbuf, n);

	return err;
}

/*
 * Todo: align address to 4 bytes.
 */
s32 _sdio_local_write(struct rtl8192cd_priv *priv, u32 addr, u32 cnt, u8 *pbuf)
{
	s32 err;
	u8 *ptmpbuf;

	if (addr & 0x3)
		printk("%s, address must be 4 bytes alignment\n", __FUNCTION__);

	if (cnt & 0x3)
		printk("%s, size must be the multiple of 4 \n", __FUNCTION__);

	HalSdioGetCmdAddr8723ASdio(priv, SDIO_LOCAL_DEVICE_ID, addr, &addr);

	if ((FALSE == GET_HAL_INTF_DATA(priv)->bMacPwrCtrlOn)
#ifdef CONFIG_LPS_LCLK
//		|| (TRUE == padapter->pwrctrlpriv.bFwCurrentInPSMode)
#endif
		)
	{
		err = _sd_cmd52_write(priv, addr, cnt, pbuf);
		return err;
	}

        ptmpbuf = (u8*)rtw_malloc(cnt);
	if (NULL == ptmpbuf)
		return -ENOMEM;

	memcpy(ptmpbuf, pbuf, cnt);

	err = _sd_write(priv, addr, cnt, ptmpbuf);

	rtw_mfree(ptmpbuf, cnt);

	return err;
}

/*
 * Todo: align address to 4 bytes.
 */
s32 sdio_local_write(struct rtl8192cd_priv *priv, u32 addr, u32 cnt, u8 *pbuf)
{
	s32 err;
	u8 *ptmpbuf;

	if (addr & 0x3)
		printk("%s, address must be 4 bytes alignment\n", __FUNCTION__);

	if (cnt & 0x3)
		printk("%s, size must be the multiple of 4 \n", __FUNCTION__);

	HalSdioGetCmdAddr8723ASdio(priv, SDIO_LOCAL_DEVICE_ID, addr, &addr);

	if ((FALSE == GET_HAL_INTF_DATA(priv)->bMacPwrCtrlOn)
#ifdef CONFIG_LPS_LCLK
		|| (TRUE == padapter->pwrctrlpriv.bFwCurrentInPSMode)
#endif
		)
	{
		err = sd_cmd52_write(priv, addr, cnt, pbuf);
		return err;
	}

        ptmpbuf = (u8*)rtw_malloc(cnt);
	if (NULL == ptmpbuf)
		return -ENOMEM;

	memcpy(ptmpbuf, pbuf, cnt);

	err = sd_write(priv, addr, cnt, ptmpbuf);

	rtw_mfree(ptmpbuf, cnt);

	return err;
}

u8 SdioLocalCmd52Read1Byte(struct rtl8192cd_priv *priv, u32 addr)
{
	u8 val = 0;

	HalSdioGetCmdAddr8723ASdio(priv, SDIO_LOCAL_DEVICE_ID, addr, &addr);
	sd_cmd52_read(priv, addr, 1, &val);

	return val;
}

u16 SdioLocalCmd52Read2Byte(struct rtl8192cd_priv *priv, u32 addr)
{
	u16 val = 0;

	HalSdioGetCmdAddr8723ASdio(priv, SDIO_LOCAL_DEVICE_ID, addr, &addr);
	sd_cmd52_read(priv, addr, 2, (u8*)&val);

	val = le16_to_cpu(val);

	return val;
}

u32 SdioLocalCmd52Read4Byte(struct rtl8192cd_priv *priv, u32 addr)
{
	u32 val = 0;

	HalSdioGetCmdAddr8723ASdio(priv, SDIO_LOCAL_DEVICE_ID, addr, &addr);
	sd_cmd52_read(priv, addr, 4, (u8*)&val);

	val = le32_to_cpu(val);

	return val;
}

u32 SdioLocalCmd53Read4Byte(struct rtl8192cd_priv *priv, u32 addr)
{
	u32 val;

	val = 0;
	HalSdioGetCmdAddr8723ASdio(priv, SDIO_LOCAL_DEVICE_ID, addr, &addr);
	if ((FALSE == GET_HAL_INTF_DATA(priv)->bMacPwrCtrlOn)
#ifdef CONFIG_LPS_LCLK
		|| (TRUE == padapter->pwrctrlpriv.bFwCurrentInPSMode)
#endif
		)
	{
		sd_cmd52_read(priv, addr, 4, (u8*)&val);
		val = le32_to_cpu(val);
	}
	else
		val = sd_read32(priv, addr, NULL);

	return val;
}

void SdioLocalCmd52Write1Byte(struct rtl8192cd_priv *priv, u32 addr, u8 v)
{
	HalSdioGetCmdAddr8723ASdio(priv, SDIO_LOCAL_DEVICE_ID, addr, &addr);
	sd_cmd52_write(priv, addr, 1, &v);
}

void SdioLocalCmd52Write2Byte(struct rtl8192cd_priv *priv, u32 addr, u16 v)
{
	HalSdioGetCmdAddr8723ASdio(priv, SDIO_LOCAL_DEVICE_ID, addr, &addr);
	v = cpu_to_le16(v);
	sd_cmd52_write(priv, addr, 2, (u8*)&v);
}

void SdioLocalCmd52Write4Byte(struct rtl8192cd_priv *priv, u32 addr, u32 v)
{
	HalSdioGetCmdAddr8723ASdio(priv, SDIO_LOCAL_DEVICE_ID, addr, &addr);
	v = cpu_to_le32(v);
	sd_cmd52_write(priv, addr, 4, (u8*)&v);
}


/*
 *
 *    HAL
 *
 */
 
void InitSdioInterrupt(struct rtl8192cd_priv *priv)
{
	HAL_INTF_DATA_TYPE *pHalData;
	
	pHalData = GET_HAL_INTF_DATA(priv);
	pHalData->sdio_himr = SDIO_HIMR_RX_REQUEST_MSK
#ifdef CONFIG_SDIO_TX_INTERRUPT
			| SDIO_HIMR_AVAL_MSK
#endif
			;
}
 
void EnableSdioInterrupt(struct rtl8192cd_priv *priv)
{
	HAL_INTF_DATA_TYPE *pHalData;
	u32 himr;

	pHalData = GET_HAL_INTF_DATA(priv);
	himr = cpu_to_le32(pHalData->sdio_himr);
	sdio_local_write(priv, SDIO_REG_HIMR, 4, (u8*)&himr);

	//
	// <Roger_Notes> There are some C2H CMDs have been sent before system interrupt is enabled, e.g., C2H, CPWM.
	// So we need to clear all C2H events that FW has notified, otherwise FW won't schedule any commands anymore.
	// 2011.10.19.
	//
	RTL_W8(C2H_SYNC_BYTE, C2H_EVT_HOST_CLOSE);
}

void DisableSdioInterrupt(struct rtl8192cd_priv *priv)
{
	u32 himr;

	himr = cpu_to_le32(SDIO_HIMR_DISABLED);
	sdio_local_write(priv, SDIO_REG_HIMR, 4, (u8*)&himr);
}

static void _OneOutPipeMapping(HAL_INTF_DATA_TYPE *pHalData)
{
	pHalData->Queue2Pipe[VO_QUEUE] = pHalData->RtOutPipe[0];//VO
	pHalData->Queue2Pipe[VI_QUEUE] = pHalData->RtOutPipe[0];//VI
	pHalData->Queue2Pipe[BE_QUEUE] = pHalData->RtOutPipe[0];//BE
	pHalData->Queue2Pipe[BK_QUEUE] = pHalData->RtOutPipe[0];//BK
	
	pHalData->Queue2Pipe[BEACON_QUEUE] = pHalData->RtOutPipe[0];//BCN
	pHalData->Queue2Pipe[MGNT_QUEUE] = pHalData->RtOutPipe[0];//MGT
	pHalData->Queue2Pipe[HIGH_QUEUE] = pHalData->RtOutPipe[0];//HIGH
	pHalData->Queue2Pipe[TXCMD_QUEUE] = pHalData->RtOutPipe[0];//TXCMD
}

static void _TwoOutPipeMapping(HAL_INTF_DATA_TYPE *pHalData, BOOLEAN bWIFICfg)
{
	if (bWIFICfg) { //WMM

		//	BK, 	BE, 	VI, 	VO, 	BCN,	CMD,MGT,HIGH,HCCA
		//{  0, 	1, 	0, 	1, 	0, 	0, 	0, 	0, 		0	};
		//0:H, 1:L

		pHalData->Queue2Pipe[VO_QUEUE] = pHalData->RtOutPipe[1];//VO
		pHalData->Queue2Pipe[VI_QUEUE] = pHalData->RtOutPipe[0];//VI
		pHalData->Queue2Pipe[BE_QUEUE] = pHalData->RtOutPipe[1];//BE
		pHalData->Queue2Pipe[BK_QUEUE] = pHalData->RtOutPipe[0];//BK

		pHalData->Queue2Pipe[BEACON_QUEUE] = pHalData->RtOutPipe[0];//BCN
		pHalData->Queue2Pipe[MGNT_QUEUE] = pHalData->RtOutPipe[0];//MGT
		pHalData->Queue2Pipe[HIGH_QUEUE] = pHalData->RtOutPipe[0];//HIGH
		pHalData->Queue2Pipe[TXCMD_QUEUE] = pHalData->RtOutPipe[0];//TXCMD

	}
	else{//typical setting

		//BK, 	BE, 	VI, 	VO, 	BCN,	CMD,MGT,HIGH,HCCA
		//{  1, 	1, 	0, 	0, 	0, 	0, 	0, 	0, 		0	};
		//0:H, 1:L

		pHalData->Queue2Pipe[VO_QUEUE] = pHalData->RtOutPipe[0];//VO
		pHalData->Queue2Pipe[VI_QUEUE] = pHalData->RtOutPipe[0];//VI
		pHalData->Queue2Pipe[BE_QUEUE] = pHalData->RtOutPipe[1];//BE
		pHalData->Queue2Pipe[BK_QUEUE] = pHalData->RtOutPipe[1];//BK

		pHalData->Queue2Pipe[BEACON_QUEUE] = pHalData->RtOutPipe[0];//BCN
		pHalData->Queue2Pipe[MGNT_QUEUE] = pHalData->RtOutPipe[0];//MGT
		pHalData->Queue2Pipe[HIGH_QUEUE] = pHalData->RtOutPipe[0];//HIGH
		pHalData->Queue2Pipe[TXCMD_QUEUE] = pHalData->RtOutPipe[0];//TXCMD

	}
	
}

static void _ThreeOutPipeMapping(HAL_INTF_DATA_TYPE *pHalData, BOOLEAN bWIFICfg)
{
	if (bWIFICfg) {//for WMM

		//	BK, 	BE, 	VI, 	VO, 	BCN,	CMD,MGT,HIGH,HCCA
		//{  1, 	2, 	1, 	0, 	0, 	0, 	0, 	0, 		0	};
		//0:H, 1:N, 2:L

		pHalData->Queue2Pipe[VO_QUEUE] = pHalData->RtOutPipe[0];//VO
		pHalData->Queue2Pipe[VI_QUEUE] = pHalData->RtOutPipe[1];//VI
		pHalData->Queue2Pipe[BE_QUEUE] = pHalData->RtOutPipe[2];//BE
		pHalData->Queue2Pipe[BK_QUEUE] = pHalData->RtOutPipe[1];//BK

		pHalData->Queue2Pipe[BEACON_QUEUE] = pHalData->RtOutPipe[0];//BCN
		pHalData->Queue2Pipe[MGNT_QUEUE] = pHalData->RtOutPipe[0];//MGT
		pHalData->Queue2Pipe[HIGH_QUEUE] = pHalData->RtOutPipe[0];//HIGH
		pHalData->Queue2Pipe[TXCMD_QUEUE] = pHalData->RtOutPipe[0];//TXCMD

	}
	else{//typical setting

		//	BK, 	BE, 	VI, 	VO, 	BCN,	CMD,MGT,HIGH,HCCA
		//{  2, 	2, 	1, 	0, 	0, 	0, 	0, 	0, 		0	};
		//0:H, 1:N, 2:L

		pHalData->Queue2Pipe[VO_QUEUE] = pHalData->RtOutPipe[0];//VO
		pHalData->Queue2Pipe[VI_QUEUE] = pHalData->RtOutPipe[1];//VI
		pHalData->Queue2Pipe[BE_QUEUE] = pHalData->RtOutPipe[2];//BE
		pHalData->Queue2Pipe[BK_QUEUE] = pHalData->RtOutPipe[2];//BK

		pHalData->Queue2Pipe[BEACON_QUEUE] = pHalData->RtOutPipe[0];//BCN
		pHalData->Queue2Pipe[MGNT_QUEUE] = pHalData->RtOutPipe[0];//MGT
		pHalData->Queue2Pipe[HIGH_QUEUE] = pHalData->RtOutPipe[0];//HIGH
		pHalData->Queue2Pipe[TXCMD_QUEUE] = pHalData->RtOutPipe[0];//TXCMD
	}

}

static BOOLEAN _MappingOutPipe(struct rtl8192cd_priv *priv, u8 NumOutPipe)
{
	HAL_INTF_DATA_TYPE* pHalData = GET_HAL_INTF_DATA(priv);
	BOOLEAN	 bWIFICfg = (priv->pmib->dot11OperationEntry.wifi_specific) ? TRUE : FALSE;
	
	BOOLEAN result = TRUE;

	switch(NumOutPipe)
	{
		case 2:
			_TwoOutPipeMapping(pHalData, bWIFICfg);
			break;
		case 3:
			_ThreeOutPipeMapping(pHalData, bWIFICfg);
			break;
		case 1:
			_OneOutPipeMapping(pHalData);
			break;
		default:
			result = FALSE;
			break;
	}

	return result;
	
}


void rtl8188es_interface_configure(struct rtl8192cd_priv *priv)
{
	HAL_INTF_DATA_TYPE *pHalData = GET_HAL_INTF_DATA(priv);
	BOOLEAN	 bWiFiConfig = (priv->pmib->dot11OperationEntry.wifi_specific) ? TRUE : FALSE;


	pHalData->RtOutPipe[0] = WLAN_TX_HIQ_DEVICE_ID;
	pHalData->RtOutPipe[1] = WLAN_TX_MIQ_DEVICE_ID;
	pHalData->RtOutPipe[2] = WLAN_TX_LOQ_DEVICE_ID;

	if (bWiFiConfig)
		pHalData->OutEpNumber = 2;
	else
		pHalData->OutEpNumber = SDIO_MAX_TX_QUEUE;

	switch(pHalData->OutEpNumber){
		case 3:
			pHalData->OutEpQueueSel=TX_SELE_HQ| TX_SELE_LQ|TX_SELE_NQ;
			break;
		case 2:
			pHalData->OutEpQueueSel=TX_SELE_HQ| TX_SELE_NQ;
			break;
		case 1:
			pHalData->OutEpQueueSel=TX_SELE_HQ;
			break;
		default:
			break;
	}

	// The QUEUE-to-OUT Pipe mapping must match _InitQueuePriority() settings
	_MappingOutPipe(priv, pHalData->OutEpNumber);
}

#ifdef CONFIG_SDIO_TX_IN_INTERRUPT
s32 sd_tx_rx_hdl(struct rtl8192cd_priv *priv)
{
	HAL_INTF_DATA_TYPE *pHalData = GET_HAL_INTF_DATA(priv);
	struct priv_shared_info *pshare = priv->pshare;
	
	struct recv_buf *precvbuf = NULL;
	s32 err = 0;
	int nr_recvbuf = 0;
	int nr_xmitbuf = 0;
	int nr_handle_recvbuf = 0;
	int loop;
	int handle_tx;
	
	do {
		if ((TRUE == pshare->bDriverStopped) || (TRUE == pshare->bSurpriseRemoved))
			break;
		
		handle_tx = 0;
		
		//Sometimes rx length will be zero. driver need to use cmd53 read again.
		if (pHalData->SdioRxFIFOSize == 0)
		{
			u32 buf[2];
			u8 *data = (u8*) buf;
			u32 sdio_hisr;
			
			err = _sdio_local_read(priv, SDIO_REG_HISR, 8, data);
			if (err)
				break;
			
			sdio_hisr = le32_to_cpu(*(u32*)data);
			if (sdio_hisr & SDIO_HISR_RX_REQUEST)
				pHalData->SdioRxFIFOSize = le16_to_cpu(*(u16*)&data[4]);
			
			if (pHalData->SdioTxIntStatus & BIT(SDIO_TX_INT_SETUP_TH))
			{
				if (sdio_hisr & SDIO_HISR_AVAL)
				{
					if (test_and_clear_bit(SDIO_TX_INT_SETUP_TH, &pHalData->SdioTxIntStatus)) {
						set_bit(SDIO_TX_INT_WORKING, &pHalData->SdioTxIntStatus);
						
						// Invalidate TX Free Page Threshold
						RTL_W8(reg_freepage_thres[pHalData->SdioTxIntQIdx], 0xFF);
						
						HalQueryTxBufferStatus8189ESdio2(priv);
						
						for (loop = priv->pmib->miscEntry.max_handle_xmitbuf; loop > 0; --loop) {
							if (rtl8188es_dequeue_writeport(priv, SDIO_TX_ISR) == FAIL)
								break;
							++nr_xmitbuf;
						}
						++handle_tx;
					}
				}
			}

#ifdef SDIO_AP_PS
            else if (pshare->offload_function_ctrl)
            {
                // do nothing. This purpose is to stop submitting any packet in AP offload (PS) state.
            }
#endif
			else {
				if ((0 == pHalData->SdioRxFIFOSize) || (nr_handle_recvbuf >= priv->pmib->miscEntry.max_handle_recvbuf))
				if (!(pshare->xmit_thread_state & XMIT_THREAD_STATE_RUNNING)
						&& (pHalData->SdioTxIntStatus & BIT(SDIO_TX_INT_WORKING))
						&& (_rtw_queue_empty(&pshare->pending_xmitbuf_queue) == FALSE))
				{
                    if (!pHalData->WaitSdioTxOQT || (HalQueryTxOQTBufferStatus8189ESdio(priv)
                        && rtw_sdio_check_TxOQT_space(priv, pHalData->WaitSdioTxOQTSpace)))
				{
					for (loop = priv->pmib->miscEntry.max_handle_xmitbuf; loop > 0; --loop) {
						if (rtl8188es_dequeue_writeport(priv, SDIO_RX_ISR) == FAIL)
							break;
						++nr_xmitbuf;
					}
					++handle_tx;
					nr_handle_recvbuf = 0;
				}
				}
			}
		}

		if (pHalData->SdioRxFIFOSize)
		{
            if (NULL == precvbuf)
            {
                precvbuf = sd_recv_rxfifo(priv, pHalData->SdioRxFIFOSize);
            } 
            else 
            {
                nr_recvbuf++;
                nr_handle_recvbuf++;
                sd_rxhandler(priv, precvbuf);
                
                precvbuf = sd_recv_rxfifo(priv, pHalData->SdioRxFIFOSize);
            }
            pHalData->SdioRxFIFOSize = 0;
        }
        else if (0 == handle_tx)
        {
            if (precvbuf) 
            {
                nr_recvbuf++;
                sd_rxhandler(priv, precvbuf);
                precvbuf = NULL;
            }
            break;
        }

	} while (1);
    if (precvbuf) 
    {
        sd_rxhandler(priv, precvbuf);
    }
	
	if (test_and_clear_bit(SDIO_TX_INT_WORKING, &pHalData->SdioTxIntStatus)
			&& !(pHalData->SdioTxIntStatus & BIT(SDIO_TX_INT_SETUP_TH))) {
		if (_rtw_queue_empty(&pshare->pending_xmitbuf_queue) == FALSE) {
			if (test_and_set_bit(WAKE_EVENT_XMIT, &pshare->wake_event) == 0)
				wake_up_process(pshare->xmit_thread);
		}
	}
	
	priv->pshare->nr_recvbuf_handled_in_irq = nr_recvbuf;
	priv->pshare->nr_xmitbuf_handled_in_irq += nr_xmitbuf;
	
	return err;
}

#else // !CONFIG_SDIO_TX_IN_INTERRUPT
s32 sd_rx_request_hdl(struct rtl8192cd_priv *priv)
{
	HAL_INTF_DATA_TYPE *pHalData = GET_HAL_INTF_DATA(priv);
	struct priv_shared_info *pshare = priv->pshare;
	
	struct recv_buf *precvbuf = NULL;
	s32 err = 0;
	int nr_recvbuf = 0;
	int nr_handle_recvbuf = 0;
	
	do {
		if ((TRUE == pshare->bDriverStopped) || (TRUE == pshare->bSurpriseRemoved))
			break;
		
		//Sometimes rx length will be zero. driver need to use cmd53 read again.
		if (pHalData->SdioRxFIFOSize == 0)
		{
			u32 buf[2];
			u8 *data = (u8*) buf;
			u32 sdio_hisr;
			
			err = _sdio_local_read(priv, SDIO_REG_HISR, 8, data);
			if (err)
				break;
			
			sdio_hisr = le32_to_cpu(*(u32*)data);
			if (sdio_hisr & SDIO_HISR_RX_REQUEST)
				pHalData->SdioRxFIFOSize = le16_to_cpu(*(u16*)&data[4]);
		}

		if (pHalData->SdioRxFIFOSize)
		{
			precvbuf = sd_recv_rxfifo(priv, pHalData->SdioRxFIFOSize);
			
			if (precvbuf) {
				nr_recvbuf++;
				sd_rxhandler(priv, precvbuf);
			}
			
			pHalData->SdioRxFIFOSize = 0;
		} else {
			break;
		}
	} while (1);
	
	priv->pshare->nr_recvbuf_handled_in_irq = nr_recvbuf;
	
	return err;
}
#endif // CONFIG_SDIO_TX_IN_INTERRUPT

void sd_int_dpc(struct rtl8192cd_priv *priv)
{
	HAL_INTF_DATA_TYPE *pHalData = GET_HAL_INTF_DATA(priv);
	struct priv_shared_info *pshare = priv->pshare;

	if (pHalData->sdio_hisr & SDIO_HISR_CPWM1)
	{
		unsigned char state;

		_sdio_local_read(priv, SDIO_REG_HCPWM1, 1, &state);
	}

	if (pHalData->sdio_hisr & SDIO_HISR_TXERR)
	{
		u8 *status;
		u32 addr;

		status = _rtw_malloc(4);
		if (status)
		{
			addr = TXDMA_STATUS;
			HalSdioGetCmdAddr8723ASdio(priv, WLAN_IOREG_DEVICE_ID, addr, &addr);
			_sd_read(priv, addr, 4, status);
			_sd_write(priv, addr, 4, status);
			printk("%s: SDIO_HISR_TXERR (0x%08x)\n", __func__, le32_to_cpu(*(u32*)status));
			priv->pshare->tx_dma_err++;
			_rtw_mfree(status, 4);
		} else {
			printk("%s: SDIO_HISR_TXERR, but can't allocate memory to read status!\n", __func__);
		}
	}

#ifdef CONFIG_INTERRUPT_BASED_TXBCN

	if (pHalData->sdio_hisr & SDIO_HISR_BCNERLY_INT)
	{
		if (priv->timoffset)
			update_beacon(priv);
	}
	
	#ifdef  CONFIG_INTERRUPT_BASED_TXBCN_BCN_OK_ERR
	if (pHalData->sdio_hisr & (SDIO_HISR_TXBCNOK|SDIO_HISR_TXBCNERR))
	{
	}
	#endif
#endif //CONFIG_INTERRUPT_BASED_TXBCN

	if (pHalData->sdio_hisr & SDIO_HISR_C2HCMD)
	{
		printk("%s: C2H Command\n", __func__);
	}

#ifdef CONFIG_SDIO_TX_IN_INTERRUPT
	if (pHalData->sdio_hisr & (SDIO_HISR_AVAL|SDIO_HISR_RX_REQUEST))
	{
		// Handle unexpected TX interrupt
		if ((pHalData->sdio_hisr & SDIO_HISR_AVAL)
				&& !(pHalData->SdioTxIntStatus & BIT(SDIO_TX_INT_SETUP_TH)))
		{
			HalQueryTxBufferStatus8189ESdio2(priv);
		}
	
		if (sd_tx_rx_hdl(priv) == -ENOMEDIUM) {
			pshare->bSurpriseRemoved = TRUE;
			return;
		}
	}

#else // !CONFIG_SDIO_TX_IN_INTERRUPT
#ifdef CONFIG_SDIO_TX_INTERRUPT
	if (pHalData->sdio_hisr & SDIO_HISR_AVAL)
	{
		if (test_and_clear_bit(SDIO_TX_INT_SETUP_TH, &pHalData->SdioTxIntStatus)) {
			// Invalidate TX Free Page Threshold
			RTL_W8(reg_freepage_thres[pHalData->SdioTxIntQIdx], 0xFF);
			
			if (test_and_set_bit(WAKE_EVENT_XMIT, &pshare->wake_event) == 0)
				wake_up_process(pshare->xmit_thread);
		}
	}
#endif
	
	if (pHalData->sdio_hisr & SDIO_HISR_RX_REQUEST)
	{
		pHalData->sdio_hisr ^= SDIO_HISR_RX_REQUEST;
		
		if (sd_rx_request_hdl(priv) == -ENOMEDIUM) {
			pshare->bSurpriseRemoved = TRUE;
			return;
		}
	}
#endif // CONFIG_SDIO_TX_IN_INTERRUPT
}

static void sd_sync_int_hdl(struct sdio_func *func)
{
	struct net_device *dev;
	struct rtl8192cd_priv *priv;
	struct priv_shared_info *pshare;
	HAL_INTF_DATA_TYPE *pHalData;
	u8 data[4];
#if defined(WLAN_PLATFORM_BALONG_V3)
{
    static unsigned long  s_jiffies_timeout = 0;
    if ((0 == s_jiffies_timeout) || time_after(jiffies, s_jiffies_timeout))
    {
        if (0 != s_jiffies_timeout)
        {
            wlan_kill_watchdog();
        }
        s_jiffies_timeout = jiffies + msecs_to_jiffies(5000); /* ��?1����?����??????(ms) */
    }
}
#endif /*WLAN_PLATFORM_QUALCOMM_9x15*/
	dev = sdio_get_drvdata(func);
	// check if surprise removal occurs ? If yes, return right now.
	if (NULL == dev)
		return;
	
#ifdef NETDEV_NO_PRIV
	priv = ((struct rtl8192cd_priv *)netdev_priv(dev))->wlan_priv;
#else
	priv = dev->priv;
#endif
	pshare = priv->pshare;
	
	if ((TRUE == pshare->bDriverStopped) || (TRUE == pshare->bSurpriseRemoved))
		return;
	
	++pshare->nr_interrupt;
    DisableSdioInterrupt(priv);
    
	if (_sdio_local_read(priv, SDIO_REG_HISR, 4, data)) {
        printk("not wifi hisr\n");
        goto out_isr;
		//return;
    }
    
	pHalData = GET_HAL_INTF_DATA(priv);
	pHalData->sdio_hisr = le32_to_cpu(*(u32*)data);

	if (pHalData->sdio_hisr & pHalData->sdio_himr)
	{
		u32 v32;
		pHalData->sdio_hisr &= pHalData->sdio_himr;
		
		// Reduce the frequency of RX Request Interrupt during RX handling
		//DisableSdioInterrupt(priv);

		// clear HISR
		v32 = pHalData->sdio_hisr & MASK_SDIO_HISR_CLEAR;
		if (v32) {
			v32 = cpu_to_le32(v32);
			_sdio_local_write(priv, SDIO_REG_HISR, 4, (u8*)&v32);
		}

		sd_int_dpc(priv);
		
		//EnableSdioInterrupt(priv);
	}
	else
	{
		DEBUG_WARN("%s: HISR(0x%08x) and HIMR(0x%08x) not match!\n",
				__FUNCTION__, pHalData->sdio_hisr, pHalData->sdio_himr);
	}

out_isr:
    EnableSdioInterrupt(priv);
}

int sdio_alloc_irq(struct rtl8192cd_priv *priv)
{
	struct sdio_func *func;
	int err;

	func = priv->pshare->psdio_func;
	
	sdio_claim_host(func);
	
	err = sdio_claim_irq(func, &sd_sync_int_hdl);
	
	sdio_release_host(func);
	
	if (err)
		printk(KERN_CRIT "%s: sdio_claim_irq FAIL(%d)!\n", __func__, err);
	
	return err;
}

int sdio_free_irq(struct rtl8192cd_priv *priv)
{
	struct sdio_func *func;
	int err;

	func = priv->pshare->psdio_func;
	
	sdio_claim_host(func);
	
	err = sdio_release_irq(func);
	
	sdio_release_host(func);
	
	if (err)
		printk(KERN_CRIT "%s: sdio_release_irq FAIL(%d)!\n", __func__, err);
	
	return err;
}

static int sdio_init(struct rtl8192cd_priv *priv)
{
	struct priv_shared_info *pshare = priv->pshare;
	struct sdio_func *func = pshare->psdio_func;
	int err;
	
	sdio_claim_host(func);

	err = sdio_enable_func(func);
	if (err) {
		printk(KERN_CRIT "%s: sdio_enable_func FAIL(%d)!\n", __func__, err);
		goto release;
	}

	err = sdio_set_block_size(func, 512);
	if (err) {
		printk(KERN_CRIT "%s: sdio_set_block_size FAIL(%d)!\n", __func__, err);
		goto release;
	}
	pshare->block_transfer_len = 512;
	pshare->tx_block_mode = 1;
	pshare->rx_block_mode = 1;

release:
	sdio_release_host(func);
	return err;
}

static void sdio_deinit(struct rtl8192cd_priv *priv)
{
	struct sdio_func *func;
	int err;

	func = priv->pshare->psdio_func;

	if (func) {
		sdio_claim_host(func);
		
		err = sdio_disable_func(func);
		if (err)
			printk(KERN_ERR "%s: sdio_disable_func(%d)\n", __func__, err);
/*
		err = sdio_release_irq(func);
		if (err)
			printk(KERN_ERR "%s: sdio_release_irq(%d)\n", __func__, err);
*/
		sdio_release_host(func);
	}
}

int sdio_dvobj_init(struct rtl8192cd_priv *priv)
{
	int err = 0;
	
	priv->pshare->pHalData = (HAL_INTF_DATA_TYPE *) rtw_zmalloc(sizeof(HAL_INTF_DATA_TYPE));
	if (NULL == priv->pshare->pHalData)
		return -ENOMEM;
	
	if ((err = sdio_init(priv)) != 0)
		goto fail;
	
	priv->pshare->version_id = VERSION_8188E;

	check_chipID_MIMO(priv);
	
	// family_mark: Move from xxx_init_one() to xxx_open() to let dynamically change OutPipe mapping
	//rtl8188es_interface_configure(priv);

	return 0;
	
fail:
	rtw_mfree(priv->pshare->pHalData, sizeof(HAL_INTF_DATA_TYPE));
	priv->pshare->pHalData = NULL;
	
	return err;
}

void sdio_dvobj_deinit(struct rtl8192cd_priv *priv)
{
	sdio_deinit(priv);

	if (priv->pshare->pHalData) {
		rtw_mfree(priv->pshare->pHalData, sizeof(HAL_INTF_DATA_TYPE));
		priv->pshare->pHalData = NULL;
	}
}

void rtw_dev_unload(struct rtl8192cd_priv *priv)
{
	struct priv_shared_info *pshare;
	
	pshare = priv->pshare;
	pshare->bDriverStopped = TRUE;

	if (FALSE == pshare->bSurpriseRemoved) {
		DisableSdioInterrupt(priv);
		sdio_free_irq(priv);
	}
	
#ifdef SMART_REPEATER_MODE
	if (!pshare->switch_chan_rp)
#endif
	if (pshare->cmd_thread) {
		if (test_and_set_bit(WAKE_EVENT_CMD, &pshare->wake_event) == 0)
			wake_up_process(pshare->cmd_thread);
		printk("[%s] cmd_thread", __FUNCTION__);
		wait_for_completion(&pshare->cmd_thread_done);
		printk(" terminate\n");
		pshare->cmd_thread = NULL;
	}
	
	if (pshare->xmit_thread) {
		if (test_and_set_bit(WAKE_EVENT_XMIT, &pshare->wake_event) == 0)
			wake_up_process(pshare->xmit_thread);
		printk("[%s] xmit_thread", __FUNCTION__);
		wait_for_completion(&pshare->xmit_thread_done);
		printk(" terminate\n");
		pshare->xmit_thread = NULL;
	}

	if (FALSE == pshare->bSurpriseRemoved) {
		rtl8192cd_stop_hw(priv);
 		pshare->bSurpriseRemoved = TRUE;
	}
}

#ifdef CONFIG_SDIO_RESERVE_MASSIVE_PUBLIC_PAGE
void _InitQueueReservedPage(struct rtl8192cd_priv *priv)
{
	HAL_INTF_DATA_TYPE	*pHalData	= GET_HAL_INTF_DATA(priv);
	
	u32			numHQ		= 0;
	u32			numLQ		= 0;
	u32			numNQ		= 0;
	u32			numPubQ;
	u32			value32;
	u8			value8;

	switch (pHalData->Queue2Pipe[BE_QUEUE]) {
	case WLAN_TX_HIQ_DEVICE_ID:	numHQ = 9; break;
	case WLAN_TX_MIQ_DEVICE_ID:	numNQ = 9; break;
	case WLAN_TX_LOQ_DEVICE_ID:	numLQ = 9; break;
	}
	
	value8 = (u8)_NPQ(numNQ);
	RTL_W8(RQPN_NPQ, value8);

	numPubQ = TX_TOTAL_PAGE_NUMBER_88E - numHQ - numLQ - numNQ;

	// TX DMA
	value32 = _HPQ(numHQ) | _LPQ(numLQ) | _PUBQ(numPubQ) | LD_RQPN;
	RTL_W32(RQPN, value32);
}
#else // !CONFIG_SDIO_RESERVE_MASSIVE_PUBLIC_PAGE
void _InitQueueReservedPage(struct rtl8192cd_priv *priv)
{
	HAL_INTF_DATA_TYPE	*pHalData	= GET_HAL_INTF_DATA(priv);
	
	u32			numHQ		= 0;
	u32			numLQ		= 0;
	u32			numNQ		= 0;
	u32			numPubQ;
	u32			value32;
	u8			value8;
	
	BOOLEAN		bWiFiConfig	= ((priv->pmib->dot11OperationEntry.wifi_specific) ? TRUE : FALSE);
	
	if (bWiFiConfig)
	{
		if (pHalData->OutEpQueueSel & TX_SELE_HQ)
		{
			numHQ =  0x30;
		}

		if (pHalData->OutEpQueueSel & TX_SELE_LQ)
		{
			numLQ = 0x30;
		}

		// NOTE: This step shall be proceed before writting REG_RQPN.
		if (pHalData->OutEpQueueSel & TX_SELE_NQ) {
			numNQ = 0x30;
		}
		value8 = (u8)_NPQ(numNQ);
		RTL_W8(RQPN_NPQ, value8);

		numPubQ = TX_TOTAL_PAGE_NUMBER_88E - numHQ - numLQ - numNQ;

		// TX DMA
		value32 = _HPQ(numHQ) | _LPQ(numLQ) | _PUBQ(numPubQ) | LD_RQPN;
		RTL_W32(RQPN, value32);
	}
	else
	{
		RTL_W16(RQPN_NPQ, 0x0000);
		RTL_W32(RQPN, 0x80a00900);
	}
}
#endif // CONFIG_SDIO_RESERVE_MASSIVE_PUBLIC_PAGE

static void _InitNormalChipRegPriority(struct rtl8192cd_priv *priv,
	u16 beQ, u16 bkQ, u16 viQ, u16 voQ, u16 mgtQ, u16 hiQ)
{
	u16 value16 = (RTL_R16(TRXDMA_CTRL) & 0x7);

	value16 |=	_TXDMA_BEQ_MAP(beQ) 	| _TXDMA_BKQ_MAP(bkQ) |
				_TXDMA_VIQ_MAP(viQ) 	| _TXDMA_VOQ_MAP(voQ) |
				_TXDMA_MGQ_MAP(mgtQ)| _TXDMA_HIQ_MAP(hiQ);
	
	RTL_W16(TRXDMA_CTRL, value16);
}

static void _InitNormalChipOneOutEpPriority(struct rtl8192cd_priv *priv)
{
	HAL_INTF_DATA_TYPE *pHalData = GET_HAL_INTF_DATA(priv);
	
	u16	value = 0;
	switch(pHalData->OutEpQueueSel)
	{
		case TX_SELE_HQ:
			value = QUEUE_HIGH;
			break;
		case TX_SELE_LQ:
			value = QUEUE_LOW;
			break;
		case TX_SELE_NQ:
			value = QUEUE_NORMAL;
			break;
		default:
			//RT_ASSERT(FALSE,("Shall not reach here!\n"));
			break;
	}
	
	_InitNormalChipRegPriority(priv, value, value, value, value, value, value);

}

static void _InitNormalChipTwoOutEpPriority(struct rtl8192cd_priv *priv)
{
	HAL_INTF_DATA_TYPE *pHalData = GET_HAL_INTF_DATA(priv);
	u16	beQ,bkQ,viQ,voQ,mgtQ,hiQ;
	
	u16	valueHi = 0;
	u16	valueLow = 0;
	
	switch(pHalData->OutEpQueueSel)
	{
		case (TX_SELE_HQ | TX_SELE_LQ):
			valueHi = QUEUE_HIGH;
			valueLow = QUEUE_LOW;
			break;
		case (TX_SELE_NQ | TX_SELE_LQ):
			valueHi = QUEUE_NORMAL;
			valueLow = QUEUE_LOW;
			break;
		case (TX_SELE_HQ | TX_SELE_NQ):
			valueHi = QUEUE_HIGH;
			valueLow = QUEUE_NORMAL;
			break;
		default:
			//RT_ASSERT(FALSE,("Shall not reach here!\n"));
			break;
	}

	if(!priv->pmib->dot11OperationEntry.wifi_specific){
		beQ		= valueLow;
		bkQ		= valueLow;
		viQ		= valueHi;
		voQ		= valueHi;
		mgtQ	= valueHi; 
		hiQ		= valueHi;
	}
	else{//for WMM ,CONFIG_OUT_EP_WIFI_MODE
		beQ		= valueLow;
		bkQ		= valueHi;
		viQ		= valueHi;
		voQ		= valueLow;
		mgtQ	= valueHi;
		hiQ		= valueHi;
	}
	
	_InitNormalChipRegPriority(priv,beQ,bkQ,viQ,voQ,mgtQ,hiQ);

}

static void _InitNormalChipThreeOutEpPriority(struct rtl8192cd_priv *priv)
{
	u16			beQ,bkQ,viQ,voQ,mgtQ,hiQ;

	if(!priv->pmib->dot11OperationEntry.wifi_specific){// typical setting
		beQ		= QUEUE_LOW;
		bkQ 		= QUEUE_LOW;
		viQ 		= QUEUE_NORMAL;
		voQ 		= QUEUE_HIGH;
		mgtQ 	= QUEUE_HIGH;
		hiQ 		= QUEUE_HIGH;
	}
	else{// for WMM
		beQ		= QUEUE_LOW;
		bkQ 		= QUEUE_NORMAL;
		viQ 		= QUEUE_NORMAL;
		voQ 		= QUEUE_HIGH;
		mgtQ 	= QUEUE_HIGH;
		hiQ 		= QUEUE_HIGH;
	}
	
	_InitNormalChipRegPriority(priv,beQ,bkQ,viQ,voQ,mgtQ,hiQ);
}

static void _InitNormalChipQueuePriority(struct rtl8192cd_priv *priv)
{
	HAL_INTF_DATA_TYPE *pHalData = GET_HAL_INTF_DATA(priv);

	switch(pHalData->OutEpNumber)
	{
		case 1:
			_InitNormalChipOneOutEpPriority(priv);
			break;
		case 2:
			_InitNormalChipTwoOutEpPriority(priv);
			break;
		case 3:
			_InitNormalChipThreeOutEpPriority(priv);
			break;
		default:
			//RT_ASSERT(FALSE,("Shall not reach here!\n"));
			break;
	}
}

void _InitQueuePriority(struct rtl8192cd_priv *priv)
{
	_InitNormalChipQueuePriority(priv);
}

static void HalRxAggr8188ESdio(struct rtl8192cd_priv *priv)
{
	u8	valueDMATimeout;
	u8	valueDMAPageCount;
	
	if (priv->pmib->dot11OperationEntry.wifi_specific)
	{
		// 2010.04.27 hpfan
		// Adjust RxAggrTimeout to close to zero disable RxAggr, suggested by designer
		// Timeout value is calculated by 34 / (2^n)
		valueDMATimeout = 0x0f;
		valueDMAPageCount = 0x01;
	}
	else
	{
		valueDMATimeout = 0x06;
		//valueDMAPageCount = 0x0F;
		//valueDMATimeout = 0x0a;
		valueDMAPageCount = 0x24;
	}
	
	RTL_W8(RXDMA_AGG_PG_TH+1, valueDMATimeout);
	RTL_W8(RXDMA_AGG_PG_TH, valueDMAPageCount);
}

void sdio_AggSettingRxUpdate(struct rtl8192cd_priv *priv)
{
	u8 valueDMA;
	
	valueDMA = RTL_R8(TRXDMA_CTRL);
	valueDMA |= RXDMA_AGG_EN;
	RTL_W8(TRXDMA_CTRL, valueDMA);
}

void _initSdioAggregationSetting(struct rtl8192cd_priv *priv)
{
	// Tx aggregation setting
	//sdio_AggSettingTxUpdate(priv);

	// Rx aggregation setting
	HalRxAggr8188ESdio(priv);
	sdio_AggSettingRxUpdate(priv);
}

//
//	Description:
//		Query SDIO Local register to get the current number of TX OQT Free Space.
//
u8 HalQueryTxOQTBufferStatus8189ESdio(struct rtl8192cd_priv *priv)
{
	HAL_INTF_DATA_TYPE *pHalData = GET_HAL_INTF_DATA(priv);
	pHalData->SdioTxOQTFreeSpace = SdioLocalCmd52Read1Byte(priv, SDIO_REG_OQT_FREE_SPACE);
	return TRUE;
}

//
//	Description:
//		Query SDIO Local register to get the current number of Free TxPacketBuffer page.
//
u8 HalQueryTxBufferStatus8189ESdio(struct rtl8192cd_priv *priv)
{
	HAL_INTF_DATA_TYPE *pHalData = GET_HAL_INTF_DATA(priv);
	u32 NumOfFreePage;

	NumOfFreePage = SdioLocalCmd53Read4Byte(priv, SDIO_REG_FREE_TXPG);

	memcpy(pHalData->SdioTxFIFOFreePage, &NumOfFreePage, 4);
	DEBUG_INFO("%s: Free page for HIQ(%#x),MIDQ(%#x),LOWQ(%#x),PUBQ(%#x)\n",
			__FUNCTION__,
			pHalData->SdioTxFIFOFreePage[HI_QUEUE_IDX],
			pHalData->SdioTxFIFOFreePage[MID_QUEUE_IDX],
			pHalData->SdioTxFIFOFreePage[LOW_QUEUE_IDX],
			pHalData->SdioTxFIFOFreePage[PUBLIC_QUEUE_IDX]);
	
	return TRUE;
}

#ifdef CONFIG_SDIO_TX_IN_INTERRUPT
u8 HalQueryTxBufferStatus8189ESdio2(struct rtl8192cd_priv *priv)
{
	HAL_INTF_DATA_TYPE *pHalData = GET_HAL_INTF_DATA(priv);
	u32 NumOfFreePage;
	
	_queue *pqueue = &priv->pshare->pending_xmitbuf_queue;
	_irqL irql;
	int update = 0;

	NumOfFreePage = SdioLocalCmd53Read4Byte(priv, SDIO_REG_FREE_TXPG);
	
	_enter_critical_bh(&pqueue->lock, &irql);
	if (!priv->pshare->freepage_updated) {
		memcpy(pHalData->SdioTxFIFOFreePage, &NumOfFreePage, 4);
		update = 1;
	}
	_exit_critical_bh(&pqueue->lock, &irql);
	
	DEBUG_INFO("%s: Free page for HIQ(%#x),MIQ(%#x),LOQ(%#x),PUBQ(%#x),Update(%d)\n",
			__FUNCTION__,
			pHalData->SdioTxFIFOFreePage[HI_QUEUE_IDX],
			pHalData->SdioTxFIFOFreePage[MID_QUEUE_IDX],
			pHalData->SdioTxFIFOFreePage[LOW_QUEUE_IDX],
			pHalData->SdioTxFIFOFreePage[PUBLIC_QUEUE_IDX],
			update);
	
	return TRUE;
}
#endif

static void pre_rtl8188es_beacon_timer(unsigned long task_priv)
{
	struct rtl8192cd_priv *priv = (struct rtl8192cd_priv *)task_priv;
	struct priv_shared_info *pshare = priv->pshare;
	
	if ((pshare->bDriverStopped) || (pshare->bSurpriseRemoved)) {
		printk("[%s] bDriverStopped(%d) OR bSurpriseRemoved(%d)\n",
			__FUNCTION__, pshare->bDriverStopped, pshare->bSurpriseRemoved);
		return;
	}
	
	rtw_enqueue_timer_event(priv, &pshare->beacon_timer_event, ENQUEUE_TO_HEAD);
}

#define BEACON_EARLY_TIME		20	// unit:TU
static void rtl8188es_beacon_timer(unsigned long task_priv)
{
	struct rtl8192cd_priv *priv = (struct rtl8192cd_priv *)task_priv;
	struct priv_shared_info *pshare = priv->pshare;
	u32 beacon_interval;
    u32 timestamp[2];
    u64 time;
	u32 cur_tick, time_offset;
#ifdef MBSSID
	u32 inter_beacon_space;
	int nr_vap, idx, bcn_idx;
#endif
	u8 val8, reg_val8, late=0;
	
	beacon_interval = priv->pmib->dot11StationConfigEntry.dot11BeaconPeriod * NET80211_TU_TO_US;
	if (0 == beacon_interval) {
		printk("[%s] ERROR: beacon interval = 0\n", __FUNCTION__);
		return;
	}
	
    timestamp[1] = RTL_R32(TSFTR+4);
    timestamp[0] = RTL_R32(TSFTR);
    while (timestamp[1]) {
        time = (u64)(0xFFFFFFFF % beacon_interval + 1) * timestamp[1] + timestamp[0];
        timestamp[0] = (u32)time;
        timestamp[1] = (u32)(time >> 32);
    }
    cur_tick = timestamp[0] % beacon_interval;
	
#ifdef MBSSID
	nr_vap = pshare->nr_vap_bcn;
	if (nr_vap) {
		inter_beacon_space = pshare->inter_bcn_space;//beacon_interval / (nr_vap+1);
		idx = cur_tick / inter_beacon_space;
		if (idx < nr_vap)	// if (idx < (nr_vap+1))
			bcn_idx = idx +1;	// bcn_idx = (idx + 1) % (nr_vap+1);
		else
			bcn_idx = 0;
		priv = pshare->bcn_priv[bcn_idx];
		if (((idx+2 == nr_vap+1) && (idx < nr_vap+1)) || (0 == bcn_idx)) {
			time_offset = beacon_interval - cur_tick - BEACON_EARLY_TIME * NET80211_TU_TO_US;
			if ((s32)time_offset < 0) {
				time_offset += inter_beacon_space;
			}
		} else {
			time_offset = (idx+2)*inter_beacon_space - cur_tick - BEACON_EARLY_TIME * NET80211_TU_TO_US;
			if (time_offset > (inter_beacon_space+(inter_beacon_space >> 1))) {
				time_offset -= inter_beacon_space;
				late = 1;
			}
		}
	} else
#endif // MBSSID
	{
		time_offset = 2*beacon_interval - cur_tick - BEACON_EARLY_TIME * NET80211_TU_TO_US;
		if (time_offset > (beacon_interval+(beacon_interval >> 1))) {
			time_offset -= beacon_interval;
			late = 1;
		}
	}
	
	BUG_ON((s32)time_offset < 0);
	
	mod_timer(&pshare->beacon_timer, jiffies+usecs_to_jiffies(time_offset));
	
#ifdef UNIVERSAL_REPEATER
	if (IS_ROOT_INTERFACE(priv)) {
		if ((OPMODE & WIFI_STATION_STATE) && GET_VXD_PRIV(priv) &&
				(GET_VXD_PRIV(priv)->drv_state & DRV_STATE_VXD_AP_STARTED)) {
			priv = GET_VXD_PRIV(priv);
		}
	}
#endif
	
	if (late)
		++priv->ext_stats.beacon_er;
	
	if (priv->timoffset) {
		update_beacon(priv);
		
		// handle any buffered BC/MC frames
		reg_val8 = RTL_R8(BCN_CTRL);
		val8 = *((unsigned char *)priv->beaconbuf + priv->timoffset + 4);
		
		if (val8 & 0x01) {
			if(reg_val8 & DIS_ATIM)
				RTL_W8(BCN_CTRL, (reg_val8 & (~DIS_ATIM)));
			process_mcast_dzqueue(priv);
			priv->pkt_in_dtimQ = 0;
		} else {
			if(!(reg_val8 & DIS_ATIM))
				RTL_W8(BCN_CTRL, (reg_val8 | DIS_ATIM));
		}
	}
}

u8 rtw_init_drv_sw(struct rtl8192cd_priv *priv)
{
	if (_rtw_init_cmd_priv(priv) == FAIL)
		goto cmd_fail;
	
	if (_rtw_init_xmit_priv(priv) == FAIL)
		goto xmit_fail;

	if (_rtw_init_recv_priv(priv) == FAIL)
		goto recv_fail;
	
	init_timer(&priv->pshare->beacon_timer);
	priv->pshare->beacon_timer.data = (unsigned long)priv;
	priv->pshare->beacon_timer.function = pre_rtl8188es_beacon_timer;
	INIT_TIMER_EVENT_ENTRY(&priv->pshare->beacon_timer_event,
		rtl8188es_beacon_timer, (unsigned long)priv);
	
	return SUCCESS;

recv_fail:
	_rtw_free_xmit_priv(priv);
xmit_fail:
	_rtw_free_cmd_priv(priv);
cmd_fail:
	
	return FAIL;
}

u8 rtw_free_drv_sw(struct rtl8192cd_priv *priv)
{
	_rtw_free_recv_priv(priv);
	_rtw_free_xmit_priv(priv);
	_rtw_free_cmd_priv(priv);
	
	return SUCCESS;
}

