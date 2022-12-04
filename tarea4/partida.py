import threading
import time
from logs import *

class Partida:
    def __init__(self,capacidad,duracion,jugadores_cola,id_game):
        self.id_game = id_game
        self.partida_log = PartidaLog(obtener_juego(id_game).replace(" ","") + ".txt")
        self.jugador_host = -1
        self.capacidad = capacidad
        self.duracion = duracion
        self.jugadores_cola = jugadores_cola
        self.threadLock = threading.Lock()
        self.statusLock = threading.Lock()
        self.queueSemaphore = threading.Semaphore(jugadores_cola)
        self.en_partida = list()
        self.cola = list()
        self.status = True

    def in_game(self,jugador,pos):
        self.statusLock.acquire()
        if (self.jugador_host == -1 and len(self.en_partida) == self.capacidad) or (self.jugador_host == -1 and len(self.cola) == 0 and len(self.en_partida[pos][2]) == 0):
            self.jugador_host = jugador
        self.statusLock.release()
        if self.jugador_host == jugador:
            print("Inicio de partida")
            time.sleep(self.duracion)
            for j,s,_ in self.en_partida:
                if j != self.jugador_host:
                    s.release()
            self.jugador_host = -1
            self.threadLock.acquire()
            self.en_partida = list()
            if len(self.cola) > 0:
                self.cola[0][1].release()
            self.threadLock.release()
        else:
            self.en_partida[pos][1].acquire()
        salida_log.registrar(jugador,salida_log.obtener_tiempo())
        print(jugador,"Saliendo")

    def entrar_en_cola(self,jugador,queue,entrada):

        print(jugador,"Esperando que exista espacio en cola")
        self.queueSemaphore.acquire()
        queue.pop(0)
        lobby_log.registrar(jugador,self.id_game,entrada,lobby_log.obtener_tiempo())
        if len(queue) > 0:
            queue[0][1].release()
            self.status = True
        else:
            self.status = False

        self.threadLock.acquire()
        semaphore = threading.Semaphore(0)
        self.cola.append((jugador,semaphore,queue))
        entrada = self.partida_log.obtener_tiempo()
        print(jugador,"Ingresando a la cola")
        while len(self.en_partida) >= self.capacidad or self.cola[0][0] != jugador:
            self.threadLock.release()
            semaphore.acquire()
            self.threadLock.acquire()
        self.cola.pop(0)
        pos = len(self.en_partida)
        self.en_partida.append((jugador,semaphore,queue))
        self.partida_log.registrar(jugador,entrada,self.partida_log.obtener_tiempo())
        if len(self.cola) > 0:
            self.cola[0][1].release()
            self.status = True
        self.threadLock.release()
        self.queueSemaphore.release()
        print(jugador,"Esperando que se inicie la partida")
        self.in_game(jugador,pos)


Estandar = Partida(15,7,7,1)
Versus = Partida(2,3,4,2)
Rapida = Partida(10,6,8,3)
Navidad = Partida(12,5,10,4)