# state-devs
Checking state of devices application

<b>Depedencies (Debian):</b>
````
apt install git gcc make libcurl4-openssl-dev libmysqlclient-dev
````
<b>Installation:</b>
````
git clone https://github.com/LittleBuster/state-devs.git
cd state-devs
make
make install
cd /etc/systemd/system/
cp sshd.service sdevs.service
vim sdevs.service

#change ExecStart to "ExecStart=/usr/share/state-devs/sdevs"
#change Alias to "Alias=sdevs.service"
#delete "EnvironmentFile=-/etc/default/ssh"

vim /etc/sdevs.conf
````
