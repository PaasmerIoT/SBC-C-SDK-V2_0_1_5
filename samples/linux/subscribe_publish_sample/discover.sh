if [ -f config.h ] ; then
       out=$(sudo cat config.h | grep "wifiDiscover" | awk '{print $3}')
       echo $out

       if [ $out = 1 ] ; then
		if [ -d "firstrun" ] ; then
			firstrun=1
			#sudo rm hari.txt
			echo "libraries are already installed"
		else
			echo "installing dependencies...."
			sudo apt-get install -y libgssdp-1.0-3
			sudo apt-get install -y gupnp-tools
			sudo apt-get install -y node.js
			sudo apt-get install -y nodejs
			sudo apt-get install -y npm
			sudo npm install -g hue-cli@0.2.0
			sudo npm install -g belkin-wemo-command-line-tools
			sudo npm i -g npm
			sudo mkdir firstrun
			sudo chmod 777 firstrun
		fi
                echo "discovering wifi devices"
       else
               echo "wifi devies are not discovering"
       fi
else
       echo "you are not downloaded or place the new config file"
fi

