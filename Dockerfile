FROM ubuntu:22.04
ENV PASSWORD="password"
CMD ["/bin/sh", "-c", "su - labs"]

COPY ./solutions /root/
RUN set -ex; \
    \
    apt-get update; \
    apt-get install -y python2 python-pip python3 gdb valgrind zsh git bash systemd ruby wget curl tmux gcc neovim vim make clang sudo gcc-multilib; \
    useradd -m labs; \
    useradd -m admin; \
    usermod -aG sudo admin; \
    chsh -s $(which zsh) labs; \
    echo "labs:${PASSWORD}" | chpasswd; \
    echo "admin:${PASSWORD}" | chpasswd 

COPY ./src/ /home/labs/
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

USER labs
WORKDIR /home/labs
RUN bash -c "$(curl -fsSL https://gef.blah.cat/sh)"
RUN git clone https://github.com/blue9057/config.git
RUN mv config/* .
RUN mv zshrc .zshrc && mv bashrc .bashrc && mv zprofile .zprofile && mv gitconfig .gitconfig && mv irbrc .irbrc && mv vimrc .vimrc && mv vim .vim
RUN rm -rf ssh
RUN rm -rf config
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
RUN pip2 install pwntools
