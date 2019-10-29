# 安装完Ubuntu

1. 更新国内源

   + 备份原始文件

     ```
     sudo cp /etc/apt/sources.list /etc/apt/sources.list.backup
     ```

   + 修改source.list文件：

     ```
     sudo vim /etc/apt/sources.list
     ```

     

   +  注释原文件内的源并添加如下地址

     ```
      #阿里云
     
     deb http://mirrors.aliyun.com/ubuntu/ trusty main restricted universe multiverse deb http://mirrors.aliyun.com/ubuntu/ trusty-security main restricted universe multiverse deb http://mirrors.aliyun.com/ubuntu/ trusty-updates main restricted universe multiverse deb http://mirrors.aliyun.com/ubuntu/ trusty-proposed main restricted universe multiverse deb http://mirrors.aliyun.com/ubuntu/ trusty-backports main restricted universe multiverse deb-src http://mirrors.aliyun.com/ubuntu/ trusty main restricted universe multiverse deb-src http://mirrors.aliyun.com/ubuntu/ trusty-security main restricted universe multiverse deb-src http://mirrors.aliyun.com/ubuntu/ trusty-updates main restricted universe multiverse deb-src http://mirrors.aliyun.com/ubuntu/ trusty-proposed main restricted universe multiverse deb-src http://mirrors.aliyun.com/ubuntu/ trusty-backports main restricted universe multiverse
     ```

     [还有一些其他源，觉得没必要，你需要也可以添加](https://www.jianshu.com/p/33403fa77936)

2. 更新所有应用

   ```
   sudo apt-get update
   sudo apt-get upgrade
   ```

3. zsh,oh-my-zsh

   [参考资料](https://post.smzdm.com/p/a5k6e033/)

   [参考链接](https://www.jianshu.com/p/5f7b83ca3952)

   补充：

   oh-my-zsh的安装，直接用：

   ```
   sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
   ```

   安装，可能会被墙，无法下载，可以直接用以下方法：

   打开在GitHub上找到[这个项目](https://github.com/robbyrussell/oh-my-zsh)，打开install.sh，将其[内容](https://github.com/robbyrussell/oh-my-zsh/blob/master/tools/install.sh)复制到本地，再 sh安装，具体如下

   ```
   cat install.sh #新建文件
   vim install.sh #打开文件，就网页上的内容复制到里面
   ```

   网页上的内容：

   ```
   #!/bin/sh
   #
   # This script should be run via curl:
   #   sh -c "$(curl -fsSL https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
   # or wget:
   #   sh -c "$(wget -qO- https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
   #
   # As an alternative, you can first download the install script and run it afterwards:
   #   wget https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh
   #   sh install.sh
   #
   # You can tweak the install behavior by setting variables when running the script. For
   # example, to change the path to the Oh My Zsh repository:
   #   ZSH=~/.zsh sh install.sh
   #
   # Respects the following environment variables:
   #   ZSH     - path to the Oh My Zsh repository folder (default: $HOME/.oh-my-zsh)
   #   REPO    - name of the GitHub repo to install from (default: robbyrussell/oh-my-zsh)
   #   REMOTE  - full remote URL of the git repo to install (default: GitHub via HTTPS)
   #   BRANCH  - branch to check out immediately after install (default: master)
   #
   # Other options:
   #   CHSH    - 'no' means the installer will not change the default shell (default: yes)
   #   RUNZSH  - 'no' means the installer will not run zsh after the install (default: yes)
   #
   # You can also pass some arguments to the install script to set some these options:
   #   --skip-chsh: has the same behavior as setting CHSH to 'no'
   #   --unattended: sets both CHSH and RUNZSH to 'no'
   # For example:
   #   sh install.sh --unattended
   #
   set -e
   
   # Default settings
   ZSH=${ZSH:-~/.oh-my-zsh}
   REPO=${REPO:-robbyrussell/oh-my-zsh}
   REMOTE=${REMOTE:-https://github.com/${REPO}.git}
   BRANCH=${BRANCH:-master}
   
   # Other options
   CHSH=${CHSH:-yes}
   RUNZSH=${RUNZSH:-yes}
   
   
   command_exists() {
   	command -v "$@" >/dev/null 2>&1
   }
   
   error() {
   	echo ${RED}"Error: $@"${RESET} >&2
   }
   
   setup_color() {
   	# Only use colors if connected to a terminal
   	if [ -t 1 ]; then
   		RED=$(printf '\033[31m')
   		GREEN=$(printf '\033[32m')
   		YELLOW=$(printf '\033[33m')
   		BLUE=$(printf '\033[34m')
   		BOLD=$(printf '\033[1m')
   		RESET=$(printf '\033[m')
   	else
   		RED=""
   		GREEN=""
   		YELLOW=""
   		BLUE=""
   		BOLD=""
   		RESET=""
   	fi
   }
   
   setup_ohmyzsh() {
   	# Prevent the cloned repository from having insecure permissions. Failing to do
   	# so causes compinit() calls to fail with "command not found: compdef" errors
   	# for users with insecure umasks (e.g., "002", allowing group writability). Note
   	# that this will be ignored under Cygwin by default, as Windows ACLs take
   	# precedence over umasks except for filesystems mounted with option "noacl".
   	umask g-w,o-w
   
   	echo "${BLUE}Cloning Oh My Zsh...${RESET}"
   
   	command_exists git || {
   		error "git is not installed"
   		exit 1
   	}
   
   	if [ "$OSTYPE" = cygwin ] && git --version | grep -q msysgit; then
   		error "Windows/MSYS Git is not supported on Cygwin"
   		error "Make sure the Cygwin git package is installed and is first on the \$PATH"
   		exit 1
   	fi
   
   	git clone --depth=1 --branch "$BRANCH" "$REMOTE" "$ZSH" || {
   		error "git clone of oh-my-zsh repo failed"
   		exit 1
   	}
   
   	echo
   }
   
   setup_zshrc() {
   	# Keep most recent old .zshrc at .zshrc.pre-oh-my-zsh, and older ones
   	# with datestamp of installation that moved them aside, so we never actually
   	# destroy a user's original zshrc
   	echo "${BLUE}Looking for an existing zsh config...${RESET}"
   
   	# Must use this exact name so uninstall.sh can find it
   	OLD_ZSHRC=~/.zshrc.pre-oh-my-zsh
   	if [ -f ~/.zshrc ] || [ -h ~/.zshrc ]; then
   		if [ -e "$OLD_ZSHRC" ]; then
   			OLD_OLD_ZSHRC="${OLD_ZSHRC}-$(date +%Y-%m-%d_%H-%M-%S)"
   			if [ -e "$OLD_OLD_ZSHRC" ]; then
   				error "$OLD_OLD_ZSHRC exists. Can't back up ${OLD_ZSHRC}"
   				error "re-run the installer again in a couple of seconds"
   				exit 1
   			fi
   			mv "$OLD_ZSHRC" "${OLD_OLD_ZSHRC}"
   
   			echo "${YELLOW}Found old ~/.zshrc.pre-oh-my-zsh." \
   				"${GREEN}Backing up to ${OLD_OLD_ZSHRC}${RESET}"
   		fi
   		echo "${YELLOW}Found ~/.zshrc.${RESET} ${GREEN}Backing up to ${OLD_ZSHRC}${RESET}"
   		mv ~/.zshrc "$OLD_ZSHRC"
   	fi
   
   	echo "${GREEN}Using the Oh My Zsh template file and adding it to ~/.zshrc.${RESET}"
   
   	cp "$ZSH/templates/zshrc.zsh-template" ~/.zshrc
   	sed "/^export ZSH=/ c\\
   export ZSH=\"$ZSH\"
   " ~/.zshrc > ~/.zshrc-omztemp
   	mv -f ~/.zshrc-omztemp ~/.zshrc
   
   	echo
   }
   
   setup_shell() {
   	# Skip setup if the user wants or stdin is closed (not running interactively).
   	if [ $CHSH = no ]; then
   		return
   	fi
   
   	# If this user's login shell is already "zsh", do not attempt to switch.
   	if [ "$(basename "$SHELL")" = "zsh" ]; then
   		return
   	fi
   
   	# If this platform doesn't provide a "chsh" command, bail out.
   	if ! command_exists chsh; then
   		cat <<-EOF
   			I can't change your shell automatically because this system does not have chsh.
   			${BLUE}Please manually change your default shell to zsh${RESET}
   		EOF
   		return
   	fi
   
   	echo "${BLUE}Time to change your default shell to zsh:${RESET}"
   
   	# Prompt for user choice on changing the default login shell
   	printf "${YELLOW}Do you want to change your default shell to zsh? [Y/n]${RESET} "
   	read opt
   	case $opt in
   		y*|Y*|"") echo "Changing the shell..." ;;
   		n*|N*) echo "Shell change skipped."; return ;;
   		*) echo "Invalid choice. Shell change skipped."; return ;;
   	esac
   
   	# Check if we're running on Termux
   	case "$PREFIX" in
   		*com.termux*) termux=true; zsh=zsh ;;
   		*) termux=false ;;
   	esac
   
   	if [ "$termux" != true ]; then
   		# Test for the right location of the "shells" file
   		if [ -f /etc/shells ]; then
   			shells_file=/etc/shells
   		elif [ -f /usr/share/defaults/etc/shells ]; then # Solus OS
   			shells_file=/usr/share/defaults/etc/shells
   		else
   			error "could not find /etc/shells file. Change your default shell manually."
   			return
   		fi
   
   		# Get the path to the right zsh binary
   		# 1. Use the most preceding one based on $PATH, then check that it's in the shells file
   		# 2. If that fails, get a zsh path from the shells file, then check it actually exists
   		if ! zsh=$(which zsh) || ! grep -qx "$zsh" "$shells_file"; then
   			if ! zsh=$(grep '^/.*/zsh$' "$shells_file" | tail -1) || [ ! -f "$zsh" ]; then
   				error "no zsh binary found or not present in '$shells_file'"
   				error "change your default shell manually."
   				return
   			fi
   		fi
   	fi
   
   	# We're going to change the default shell, so back up the current one
   	if [ -n "$SHELL" ]; then
   		echo $SHELL > ~/.shell.pre-oh-my-zsh
   	else
   		grep "^$USER:" /etc/passwd | awk -F: '{print $7}' > ~/.shell.pre-oh-my-zsh
   	fi
   
   	# Actually change the default shell to zsh
   	if ! chsh -s "$zsh"; then
   		error "chsh command unsuccessful. Change your default shell manually."
   	else
   		export SHELL="$zsh"
   		echo "${GREEN}Shell successfully changed to '$zsh'.${RESET}"
   	fi
   
   	echo
   }
   
   main() {
   	# Run as unattended if stdin is closed
   	if [ ! -t 0 ]; then
   		RUNZSH=no
   		CHSH=no
   	fi
   
   	# Parse arguments
   	while [ $# -gt 0 ]; do
   		case $1 in
   			--unattended) RUNZSH=no; CHSH=no ;;
   			--skip-chsh) CHSH=no ;;
   		esac
   		shift
   	done
   
   	setup_color
   
   	if ! command_exists zsh; then
   		echo "${YELLOW}Zsh is not installed.${RESET} Please install zsh first."
   		exit 1
   	fi
   
   	if [ -d "$ZSH" ]; then
   		cat <<-EOF
   			${YELLOW}You already have Oh My Zsh installed.${RESET}
   			You'll need to remove '$ZSH' if you want to reinstall.
   		EOF
   		exit 1
   	fi
   
   	setup_ohmyzsh
   	setup_zshrc
   	setup_shell
   
   	printf "$GREEN"
   	cat <<-'EOF'
   		         __                                     __
   		  ____  / /_     ____ ___  __  __   ____  _____/ /_
   		 / __ \/ __ \   / __ `__ \/ / / /  /_  / / ___/ __ \
   		/ /_/ / / / /  / / / / / / /_/ /    / /_(__  ) / / /
   		\____/_/ /_/  /_/ /_/ /_/\__, /    /___/____/_/ /_/
   		                        /____/                       ....is now installed!
   		Please look over the ~/.zshrc file to select plugins, themes, and options.
   		p.s. Follow us on https://twitter.com/ohmyzsh
   		p.p.s. Get stickers, shirts, and coffee mugs at https://shop.planetargon.com/collections/oh-my-zsh
   	EOF
   	printf "$RESET"
   
   	if [ $RUNZSH = no ]; then
   		echo "${YELLOW}Run zsh to try it out.${RESET}"
   		exit
   	fi
   
   	exec zsh -l
   }
   
   main "$@"
   ```

   然后安装

   ```
   sh install.sh
   ```

4. 