#include <stdio.h>
#include <seccomp.h>
#include <stdlib.h>
#include <fcntl.h>

/* SECCOMP SANDBOX; Only the syscalls in the WHITELIST can be usable */
void setup_rules() {
  // Init the filter
  scmp_filter_ctx ctx;
  ctx = seccomp_init(SCMP_ACT_KILL); // default action: kill
  if (ctx == NULL)
    exit(-1);

  // setup basic whitelist
  if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open), 0) < 0)
    exit(-1);
  if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0) < 0)
    exit(-1);
  if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(lseek), 0) < 0)
    exit(-1);
  if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0) < 0)
    exit(-1);
  if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0) < 0)
    exit(-1);
  if (seccomp_load(ctx) < 0)
    exit(-1);
}

void target() {
    char buf[16];
    int fd = 0;
    read(fd, buf, 512);
}

void
_setregid(void) {
    setregid(getegid(), getegid());
}

void
_execve(void) {
    execve("/bin/sh", 0, 0);
}

void
_write(void) {
    write(1, "asdf\n", 5);
}

int main() {
    // just use open. Do nothing.
    int fd = open("/etc/issue", O_RDONLY);
    int test = 0;
    printf("Welcome to my seccomp sandbox.\n");
    printf("You can open(), read(), and exit(), but nothing else...\n");
    printf("Let's test the sandbox first.\n");
    printf("What do you want to do?\n");
    printf("1. setregid(getegid(), getegid())\n");
    printf("2. execve(\"/bin/sh\", 0, 0)\n");
    printf("3. write(1, \"asdf\\n\", 5)\n");
    printf("4. No test, I know how to exploit this program!\n");
    scanf("%d", &test);
    printf("Starting my sandbox!!!\n");
    setup_rules();
    switch (test) {
        case 1:
            _setregid();
            break;
        case 2:
            _execve();
            break;
        case 3:
            _write();
            break;
        default:
            target();
            break;
    }
}
