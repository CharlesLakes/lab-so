import threading
import time

class Partida:
    def __init__(self,capacidad,duracion,jugadores_cola):
        self.jugador_host = -1
        self.capacidad = capacidad
        self.duracion = duracion
        self.jugadores_cola = jugadores_cola
        self.threadLock = threading.Lock()
        self.statusLock = threading.Lock()
        self.queueSemaphore = threading.Semaphore(jugadores_cola)
        self.en_partida = list()
        self.cola = list()

    def in_game(self,jugador,pos):
        self.statusLock.acquire()
        if self.jugador_host == -1 and (len(self.en_partida) == self.capacidad):
            self.jugador_host = jugador
        self.statusLock.release()
        if self.jugador_host == jugador:
            print("Inicio de partida")
            time.sleep(self.duracion)
            for j,s in self.en_partida:
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
        print(jugador,"Saliendo")

    def entrar_en_cola(self,jugador,queue):

        #print(jugador,"Esperando que exista espacio en cola")
        self.queueSemaphore.acquire()
        if len(queue) > 0:
            queue[0][1].release()
        self.threadLock.acquire()
        semaphore = threading.Semaphore(0)
        self.cola.append((jugador,semaphore))
        print(jugador,"Ingresando a la cola")
        while len(self.en_partida) >= self.capacidad or self.cola[0][0] != jugador:
            self.threadLock.release()
            semaphore.acquire()
            self.threadLock.acquire()
        self.cola.pop(0)
        pos = len(self.en_partida)
        self.en_partida.append((jugador,semaphore))
        if len(self.cola) > 0:
            self.cola[0][1].release()
        self.threadLock.release()
        self.queueSemaphore.release()
        print(jugador,"Esperando que se inicie la partida")
        self.in_game(jugador,pos)


Estandar = Partida(15,7,7)
Versus = Partida(2,3,4)
Rapida = Partida(10,6,8)
Navidad = Partida(12,5,10)