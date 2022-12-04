from datetime import datetime
from threading import Lock

def obtener_juego(game):
        if game == 1:
            return "Partida Estandar"
        elif game == 2:
            return "Partida Versus"
        elif game == 3:
            return "Partida Rapida"
        elif game == 4:
            return "Partida Especial Navidad"

class Log:
    def __init__(self,filename):
        self.filename = filename
        file = open(filename,"w")
        file.write("")
        file.close()
        self.lock = Lock()
    
    def obtener_tiempo(self):
        return str(datetime.now())

    def escribir(self,data):
        file = open(self.filename,"a")
        file.write(data)
        file.close()


class LobbyLog(Log):    
    def registrar(self,jugador,game,entrada,salida):
        self.lock.acquire()
        data = f"Jugador{jugador}, {entrada}, {obtener_juego(game)}, {salida}\n"
        self.escribir(data)
        self.lock.release()

class PartidaLog(Log):    
    def registrar(self,jugador,entrada,salida):
        self.lock.acquire()
        data = f"Jugador{jugador}, {entrada}, {salida}\n"
        self.escribir(data)
        self.lock.release()

class SalidaLog(Log):    
    def registrar(self,jugador,salida):
        self.lock.acquire()
        data = f"Jugador{jugador}, {salida}\n"
        self.escribir(data)
        self.lock.release()

lobby_log = LobbyLog("Lobby.txt")
salida_log = SalidaLog("Salida.txt")