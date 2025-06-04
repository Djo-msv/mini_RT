########## SET IMAGE DESKTOP ##########

if [ ! -f ~/.background ]; then
    echo "[ERROR] .background file not found. Exiting."
    exit 1
fi

yes | cp -f ~/.background /tmp/codam-web-greeter-user-wallpaper
