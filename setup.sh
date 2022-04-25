echo "setting depedencies"
if [ "$(uname)" == "Darwin"]; then
    if hash brew 2>/dev/null; then
        brew install nasm
        brew install supervisor
        brew tap xrisk/i686-toolchain
        brew install --HEAD i686-elf-grub
        curl -s -o ~/.cross-dev.sh https://raw.githubusercontent.com/xrisk/homebrew-i686-toolchain/master/setenv.sh
        echo "[-] the cross compiler compiler has been intalled and a config file has been created"
        echo "[-] please run: 'source $HOME/cross-dev.h' before using the cross compiler"
    else
        echo "[!] please install homebrew from https://brew.sh"
        echo "[!] clifterOS uses homebrew to install dependencies"
    fi
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux"]; then
    echo pwd
    echo "[-] Running under linux distro"
    current_dir=$PWD
    cd /home/$USER
    git clone https://github.com/kanaka/noVNC
    cd $current_dir
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt-get update

    if [ -z "$TRAVIS" ]; then
        sudo apt-get install -y nasm qemu gcc-5 gcc-5-multilib grub-common xorriso grub-pc-bin supervisor xvfb x11vnc fluxbox
    else
        sudo pt-get install nasm gcc-5 gcc-5-multilib qemu grub-common xorriso grub-pc-bin supervisor xvfb x11vnc fluxbox
    fi
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
    echo "[!] clifterOS isnt available on windows operating systems"
fi