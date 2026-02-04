#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

enum mtk_spi_mode 
{
    SPI_OCTAL=1,
    SPI_QUAD,
    SPI_DUAL,
};

typedef struct mtk_spi_dev
{
    int fd;
    enum mtk_spi_mode spi_mode;
    uint32_t speed_hz;
    uint16_t delay_usecs;
    uint8_t bits_per_word;
    uint32_t mode;
    uint8_t nbits;
}mtk_spi_dev_t;

typedef struct mtk_spi_dev_config
{
    int fd; //necessary
    enum mtk_spi_mode spi_mode;
    uint32_t speed_hz;
    uint16_t delay_usecs;
    uint8_t bits_per_word;
}mtk_spi_dev_config_t;

#define MTK_DEV_CFG_DEFAULT { \
    .bits_per_word = 8, \
    .speed_hz = 48*1000*1000, \
    .delay_usecs = 90, \
    .spi_mode = SPI_DUAL \
}

int mtk_spi_init(struct mtk_spi_dev_config *dev_cfg, struct mtk_spi_dev *o_dev);
int mtk_spi_transfer(struct mtk_spi_dev *dev, const uint8_t *tx, const uint8_t *rx, size_t len);
int mtk_spi_domsg(struct mtk_spi_dev *dev, const uint8_t *tx, size_t tx_len, const uint8_t *rx, size_t rx_len);

char *get_hello();