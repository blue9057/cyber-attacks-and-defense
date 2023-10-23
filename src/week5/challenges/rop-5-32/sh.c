int main() {
    setregid(getegid(), getegid());
    execve("/bin/sh", 0, 0);
}
