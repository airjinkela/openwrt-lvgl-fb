
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <err.h>
#include <stdio.h>

#include "mtk-spi.h"


int mtk_spi_init(struct mtk_spi_dev_config *dev_cfg, struct mtk_spi_dev *o_dev)
{
    int ret;
    uint32_t mode = 0, req_mode;
    uint8_t nbits;

    if(!dev_cfg)
        return -1;

    if(dev_cfg->fd < 0)
        return -1;
    o_dev->fd = dev_cfg->fd;
    o_dev->spi_mode = dev_cfg->spi_mode;
    o_dev->speed_hz = dev_cfg->speed_hz;
    o_dev->delay_usecs = dev_cfg->delay_usecs;
    o_dev->bits_per_word = dev_cfg->bits_per_word;

    switch (o_dev->spi_mode)
    {
    case SPI_DUAL:
        nbits = 2;
        mode |= SPI_TX_DUAL;
        mode |= SPI_RX_DUAL;
        break;
    case SPI_QUAD:
        nbits = 4;
        mode |= SPI_TX_QUAD;
        mode |= SPI_RX_QUAD;
        break;
    case SPI_OCTAL:
        nbits = 8;
        mode |= SPI_TX_OCTAL;
        mode |= SPI_RX_OCTAL;
        break;
    default:
        nbits = 0;
        break;
    };

	req_mode = mode;
	ret = ioctl(o_dev->fd, SPI_IOC_WR_MODE32, &mode);
	if (ret == -1)
        goto out;
	ret = ioctl(o_dev->fd, SPI_IOC_RD_MODE32, &mode);
    if (ret == -1)
        goto out;

    if (req_mode != mode)
        printf("not support mode: 0x%x", req_mode);

    ret = ioctl(o_dev->fd, SPI_IOC_WR_BITS_PER_WORD, &o_dev->bits_per_word);
	if (ret == -1)
		printf("can't set bits per word\n");

    ret = ioctl(o_dev->fd, SPI_IOC_WR_MAX_SPEED_HZ, &o_dev->speed_hz);
	if (ret == -1)
    {
		printf("can't set max speed hz\n");
        goto out;
    }

    o_dev->mode = mode;
    o_dev->nbits = nbits;

out:
    return ret;
}

int mtk_spi_transfer(struct mtk_spi_dev *dev, const uint8_t *tx, const uint8_t *rx, size_t len)
{
    int ret;
    if(!(tx && rx)){
        ret = -1;
        goto out;
    }

    struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = len,
		.delay_usecs = dev->delay_usecs,
		.speed_hz = dev->speed_hz,
		.bits_per_word = dev->bits_per_word,
        .tx_nbits = dev->nbits,
        .rx_nbits = dev->nbits,
	};

    ret = ioctl(dev->fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
        goto out;
    ret = 0;

out:
    return ret;
}

int mtk_spi_domsg(struct mtk_spi_dev *dev, const uint8_t *tx, size_t tx_len, const uint8_t *rx, size_t rx_len)
{
    int ret;
    struct spi_ioc_transfer tr[2] = {0};
    if(!(tx && rx)){
        ret = -1;
        goto out;
    }

    tr[0].tx_buf = (unsigned long)tx,
    tr[0].len = tx_len,
    tr[0].delay_usecs = dev->delay_usecs,
    tr[0].speed_hz = dev->speed_hz,
    tr[0].bits_per_word = dev->bits_per_word,
    tr[0].tx_nbits = dev->nbits,
    tr[0].rx_nbits = dev->nbits,

    tr[1].rx_buf = (unsigned long)rx,
	tr[1].len = tx_len,
	tr[1].delay_usecs = dev->delay_usecs,
	tr[1].speed_hz = dev->speed_hz,
	tr[1].bits_per_word = dev->bits_per_word,
    tr[1].tx_nbits = dev->nbits,
    tr[1].rx_nbits = dev->nbits,

    ret = ioctl(dev->fd, SPI_IOC_MESSAGE(2), tr);
	if (ret < 1)
        goto out;
    ret = 0;

out:
    return ret;
}
