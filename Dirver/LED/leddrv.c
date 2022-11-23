#include <linux/module.h>

#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/kmod.h>
#include <linux/gfp.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/slab.h>


#define Turn_on 0x01
#define Turn_off 0x02

typedef struct gpio_leds{
	int gpio;
	struct gpio_desc *gpiod;
	int flag;
}Gpio_leds;
typedef struct ledcrtl
{
	int led_t;
	int val_t;
}Ledcrtl;


static struct class *led_class;
static Gpio_leds *gpio_leds_100ask;
static int major = 0;
int count;



/* 3. 实现对应的open/read/write等函数，填入file_operations结构�?          */

/* write(fd, &ledcrtl, 4); */  
static ssize_t led_drv_write (struct file *file, const char __user *buf, size_t size, loff_t *offset)
{
	int err;
	Ledcrtl * led;
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	err = copy_from_user(led, buf, sizeof(Ledcrtl));
	
	/* 根据次设备号和status控制LED */
	gpiod_set_value(gpio_leds_100ask[led->led_t].gpiod, led->val_t);
	
	return 1;
}

static int led_drv_open (struct inode *node, struct file *file)
{
	//int minor = iminor(node);
	int i ;
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	/* 根据次设备号初始化LED */
	for(i=0;i<count;i++)
	{
		gpiod_direction_output(gpio_leds_100ask[i].gpiod, 0);
	}
	return 0;
}
static long led_drv_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    int ret = 0;
    void __user *my_user_space = (void __user *)arg;
	int led = 0;
	switch (cmd)
	{
		case Turn_on:
		{
			ret = copy_from_user(&led, my_user_space, sizeof(led));
			gpiod_set_value(gpio_leds_100ask[led].gpiod, 1);
			break;
		}
		case Turn_off:
		{	
			ret = copy_from_user(&led, my_user_space, sizeof(led));
			gpiod_set_value(gpio_leds_100ask[led].gpiod, 0);
			break;
		}
	}
	return 1;
}

/* 定义自己的file_operations结构�?                                             */
static struct file_operations led_drv = {
	.owner	 = THIS_MODULE,
	.open    = led_drv_open,
	.write   = led_drv_write,
	.unlocked_ioctl = led_drv_ioctl,
};
	
/* 4. 从platform_device获得GPIO
 *	  把file_operations结构体告诉内核：注册驱动程序
 */
static int gpio_led_probe(struct platform_device *pdev)
{
	int err;
	struct device_node *node = pdev->dev.of_node;
	int i;
	enum of_gpio_flags flag;
	unsigned flags = GPIOF_DIR_OUT;
	
	count = of_gpio_count(node);
	if (!count)
	{
		printk("%s %s line %d, there isn't any gpio available\n", __FILE__, __FUNCTION__, __LINE__);
		return -1;
	}
	gpio_leds_100ask = (Gpio_leds*)kzalloc(sizeof(Gpio_leds) * count, GFP_KERNEL);
	for(i =0;i < count; i++)
	{
		gpio_leds_100ask[i].gpio = of_get_gpio_flags(node, i, &flag);
		if (!gpio_is_valid(gpio_leds_100ask[i].gpio))
		{
			printk("%s %s line %d, of_get_gpio_flags fail\n", __FILE__, __FUNCTION__, __LINE__);
			return -1;
		}
		gpio_leds_100ask[i].gpiod = gpio_to_desc(gpio_leds_100ask[i].gpio);
		gpio_leds_100ask[i].flag  = flag & OF_GPIO_ACTIVE_LOW;
		
		if (flag & OF_GPIO_ACTIVE_LOW)
			flags |= GPIOF_ACTIVE_LOW;
	}
	
	/* 4.2 注册file_operations 	*/
	major = register_chrdev(0, "100ask_led", &led_drv);  /* /dev/100ask_led */

	led_class = class_create(THIS_MODULE, "100ask_led_class");
	if (IS_ERR(led_class)) 
	{
		printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
		unregister_chrdev(major, "100ask_led");
		return PTR_ERR(led_class);
	}
	
	device_create(led_class, NULL, MKDEV(major, 0), NULL, "100ask_led"); /* /dev/100ask_led */
    return 0;
	
}

static int gpio_led_remove(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	int i;
	device_destroy(led_class, MKDEV(major, 0));
	class_destroy(led_class);
	unregister_chrdev(major, "100ask_led");
	for( i=0;i<count;i++)
	{
		gpiod_put(gpio_leds_100ask[i].gpiod);
	}
	kfree(gpio_leds_100ask);
    return 0;
}


static const struct of_device_id ask100_leds[] = {
    { .compatible = "100ask,leddrv" },
    { },
};

/* 1. 定义platform_driver */
static struct platform_driver gpio_led_driver = {
    .probe      = gpio_led_probe,
    .remove     = gpio_led_remove,
    .driver     = {
        .name   = "100ask_led",
        .of_match_table = ask100_leds,
    },
};

/* 2. 在入口函数注册platform_driver */
static int __init gpio_led_init(void)
{
    int err;
    
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	
    err = platform_driver_register(&gpio_led_driver); 
	
	return err;
}

/* 3. 有入口函数就应该有出口函数：卸载驱动程序时，就会去调用这个出口函数
 *     卸载platform_driver
 */
static void __exit gpio_led_exit(void)
{
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);

    platform_driver_unregister(&gpio_led_driver);
}


/* 7. 其他完善：提供设备信息，自动创建设备节点                                     */

module_init(gpio_led_init);
module_exit(gpio_led_exit);

MODULE_LICENSE("GPL");






