# Red Star OS 3.0 Kernel Source Code
The source code tree for the 2.6.38 Linux kernel as implemented in Red Star OS 3.0

## About This Repo
As I work to dig further into the mysteries of Red Star OS, the infamous North Korean
Linux distro, one thing that came to me was "where the hell is the source code?"
Initially, it didn't look like there was any source code included with Red Star OS 3.0
itself; this would make sense from the perspective of the North Korean government not
wanting any secrets of the system internals to get into the hands of anyone else, lest
the code gets reverse engineered and people find out its deep, dark secrets.

Welp, they didn't think about two packages included in the Red Star installation DVD,
now, did they?

Included on the DVD are two .rpm packages, `kernel-devel-2.6.38.8-24.rs3.0.i686.rpm`
and `kernel-headers-2.6.38.8-24.rs3.0.i686.rpm`, which contain the kernel source
code and headers. I was able to extract the contents of these two packages with
rpm2cpio, and here it all is for everyone to enjoy and see!

## Why release this source code?
Reverse engineering is always a fun thing, but in this case, it allows us to see into
how an isolated country like North Korea worked on their own, homegrown Linux distro,
but one that's filled with tools and daemons that can be used to opress their
populace. In 2015, Chaos Computer Club did a [presentation on Red Star OS](https://media.ccc.de/v/32c3-7174-lifting_the_fog_on_red_star_os), where they delved into some of its inner
workings, lifted the fog on aspects of the system's workings, and showed that despite
Korea Computer Company's best attempts to make the system look and seem secure and
unbreakable, the system was still easy enough to defang and hack into, and inspiring
many others, myself included, to want to dig further into the system to see what else
we could find and do with it. And so here we are!

## What to do with this source code
This source code is mainly for research and study purposes. If you wish to build and
debug this source code, I would recommend keeping it within a sandboxed environment.
