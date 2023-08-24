# Variants of Linux Kernel
with changes from different vendors

This project is an attempt to create a tree of changes made to the original
Linux kernel sources by different vendors. Device-specific kernel sources are
harvested from SDK and from officially provided sources.

Derivatives reside in their own branches making it easy to track changes between
branches.

Tree of branches:
- __3.10.14__ (from https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/snapshot/linux-3.10.14.tar.gz)
  - __isvp-sdk-t10-20-3.9.0__ (from ISVP-SDK-T10-20 v3.9.0)
  - __isvp-sdk-t10-20-3.12.0__ (from ISVP-SDK-T10-20 v3.12.0)
  - __isvp-sdk-t30-1.0.5__ (from ISVP-SDK-T30 v1.0.5)
  - __isvp-sdk-t31-1.1.2__ (from ISVP-SDK-T31 v1.1.2)
  - __isvp-sdk-t31-1.1.4__ (from ISVP-SDK-T31 v1.1.4)
  - __isvp-sdk-t31-1.1.5__ (from ISVP-SDK-T31 v1.1.5)
- __4.4.94__ (from https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.4.94.tar.gz)
  - __answer-t31-kernel-4.4__ (from https://gitee.com/wu-chunyu/t31-kernel-4.4/tree/master/kernel-4.4)
