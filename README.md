
#IPERF-GUI Setup
##Zweck
Grafische Oberfläche basierend auf Qt5 um Belastungstests mit dem Netzwerk Tool iperf3 auf einem Raspberry Pi 3 mit 7'' Touch Display durchzuführen.

**Server Fenster**
![Server](https://raw.github.com/ahueber/iperf-gui/master/images/server.png)

**Client Fenster**
![Client](https://raw.github.com/ahueber/iperf-gui/master/images/client.png)

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
    
Durch Aufruf von ANT werden die Source Dateien kompiliert und es wird ein Ordner "release" erstellt mit der ausführbaren Datei "iperf"

    ant
    
##Bash Skript zum Starten der Anwendung   
Aufgrund eines Bugs im QComboBox Element von Qt5 unter Raspbian muss die Anwendung mit dem -nograb Flag geöffnet werden. Am einfachsten geht dies über ein kleinen Bash Skript das wir auf den Desktop legen.

    cd ~/Desktop
    sudo nano
    
Inhalt der Datei:

    #!/bin/bash
    /home/pi/iperf-gui/iperf -nograb
    
Über die Tastenkombination CTRL-O im Nano Editor kann die Datei gespeichert werden. Nachdem ein Name eingegeben (z.B. iperf-gui.sh) und mit Enter bestätigt wurde, kann der Nano Editor über die Tastenkombintation CTRL-X geschlossen werden.

Als letztes muss noch die neu erstellte Datei ausführbar gemacht werden.

    sudo chmod +x iperf-gui.sh

Zum Starten der Anwendung muss jetzt nur noch ein Doppelklick auf das Start Skript gemacht und "Ausführen" ausgewählt werden.
    