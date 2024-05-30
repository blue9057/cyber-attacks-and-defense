FROM ubuntu:22.04
ENV PASSWORD="password"
CMD ["/bin/sh", "-c", "su - labs"]

COPY --chmod=700 ./solutions /root/
RUN set -ex; \
    \
    apt-get update; \
    apt-get install -y software-properties-common build-essential python2 python-pip file python3 language-pack-en gdb valgrind zsh git bash ruby wget curl tmux gcc vim make clang sudo gcc-multilib; \
    add-apt-repository ppa:ubuntu-toolchain-r/test; \
    apt-get update; \
    useradd -m labs; \
    useradd -m admin; \
    usermod -aG sudo admin; \
    update-locale LANG=en_US.UTF-8 LC_MESSAGES=POSIX; \
    chsh -s $(which bash) labs; \
    echo "labs:${PASSWORD}" | chpasswd; \
    echo "admin:${PASSWORD}" | chpasswd

COPY --chmod=777 ./src/ /home/labs/
RUN (cd /home/labs/week1 && make)
RUN (cd /home/labs/week2 && make)
RUN (cd /home/labs/week3 && make)
RUN (cd /home/labs/week4 && make)
RUN (cd /home/labs/week5 && make)
RUN (cd /home/labs/week6 && make)
RUN (cd /home/labs/week7 && make)
RUN chown -R labs:labs /home/labs
RUN (cd /home/labs/week1/challenges && python2 install.py)
RUN (cd /home/labs/week2/challenges && python2 install.py)
RUN (cd /home/labs/week3/challenges && python2 install.py)
RUN (cd /home/labs/week4/challenges && python2 install.py)
RUN (cd /home/labs/week5/challenges && python2 install.py)
RUN (cd /home/labs/week6/challenges && python2 install.py)
RUN (cd /home/labs/week7/challenges && python2 install.py)
RUN (wget https://github.com/pwndbg/pwndbg/releases/download/2024.02.14/pwndbg_2024.02.14_amd64.deb && apt install -y ./pwndbg_2024.02.14_amd64.deb && rm pwndbg_2024.02.14_amd64.deb)
RUN ln -s /usr/bin/python2 /usr/bin/python

USER labs
WORKDIR /home/labs
RUN (wget https://robertserver.s3.us-west-2.amazonaws.com/cand_dotfiles.tar.gz && tar -xvf cand_dotfiles.tar.gz && rm cand_dotfiles.tar.gz)
RUN bash -c "$(curl -fsSL https://gef.blah.cat/sh)"
RUN pip2 install pwntools

USER root
