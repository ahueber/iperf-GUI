
#IPERF-GUI Setup
##Zweck
Grafische Oberfläche basierend auf Qt5 um Belastungstests mit dem Netzwerk Tool iperf3 auf einem Raspberry Pi 3 mit 7'' Touch Display durchzuführen.

**Server Fenster**
![Server](https://raw.github.com/ahueber/iperf-gui/master/resources/images/server.png)

**Client Fenster**
![Client](https://raw.github.com/ahueber/iperf-gui/master/resources/images/client.png)

##Vorbereitung

Als erstes müssen die Paketquellen und installierten Pakete auf den neusten Stand gebracht werden.

    sudo apt-get update
    sudo apt-get upgrade
    
Als nächstes müssen die Qt5 Entwicklungspakete installiert werden.

    sudo apt-get install qt5-default
    
   Damit die IPERF-GUI Dateien später einfacher kompiliert werden können muss noch Apache ANT installliert werden.
   
    sudo apt-get install ant
    
Falls GIT noch nicht installiert ist kann dies über folgenden Befehl gemacht werden.

    sudo apt-get install git
      
##Installation iperf3  
Iperf3 muss mindestens in der Version 3.1 oder höher installiert sein. Zum aktuellen Zeitpunkt (Dez. 2016) ist eine tiefere Version in den APT Paketquellen, es müssen also die Debian Pakete für iperf3, sowie die benötigte Bibliothek von der offiziellen Webseite heruntergeladen werden.

    wget https://iperf.fr/download/ubuntu/iperf3_3.1.3-1_armhf.deb
    wget https://iperf.fr/download/ubuntu/libiperf0_3.1.3-1_armhf.deb
    
Als nächstes können die Pakete installiert werden (Reihenfolge beachten).
     
    sudo dpkg -i libiperf0_3.1.3-1_armhf.deb
    sudo dpkg -i iperf3_3.1.3-1_armhf.deb
      
 Danach können die heruntergeladenen Pakete wieder entfernt werden.
 
    rm libiperf0_3.1.3-1_armhf.deb
    rm iperf3_3.1.3-1_armhf.deb
    
##Installation IPERF-GUI
Zuerst müssen die Source Dateien heruntergeladen werden.

    git clone http://github.com/ahueber/iperf-gui
    
Danach wechseln wir in das neu erstellte Verzeichnis.

    cd iperf-gui/
    
Durch Aufruf von ANT werden die Source Dateien kompiliert und es wird ein Launcher "iperf-GUI" auf den Desktop gelegt

    ant
    
