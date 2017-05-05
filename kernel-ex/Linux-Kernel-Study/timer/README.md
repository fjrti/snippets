# Delay labs

- 1. short delay

use function `udelay`

```
  ndelay(5);
```

- 2. delay

create a timer

```
  // init
	struct timer_list my_timer;
	init_timer(&my_timer);

	// complete
	my_timer.expires = jiffies + 1 * HZ;
	my_timer.data = jiffies;
	my_timer.function = my_delay_function;

	// active
	add_timer(&my_timer);
```

- 3. schedule_time

use function schedule_timeout()

```
  set_current_state(TASK_INTERRUPTIBLE);
	printk(KERN_ALERT"sleep 2 sec...\n");
	schedule_timeout(2 * HZ);
```

- 4. result

The `HZ` of my VM is 250HZ

The interval of the timer is 250 ticks exactly

The interval of the schedule_timeout() is 500 tichs exactly
