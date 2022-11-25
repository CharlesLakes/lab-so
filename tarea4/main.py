import queue
import threading
from datetime import datetime
import random



def make_files():
    a = [   "PartidaEstandar.txt",
            "PartidaVersus.txt",
            "PartidaRápida.txt",
            "PartidaEspecialNavidad.txt",
            "Salida.txt"]
    for i in a:
        archivo = open(i,"w")
        archivo.close()
    return


class myThread (threading.Thread):
   def __init__(self, threadID, name, counter):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.game = random.randint(1,4)
        self.start_time = datetime.now()
        self.counter = counter
   def run(self):
        if self.game == 1:
            game="Partida Estandar"
        elif self.game == 2:
            game="Partida Versus"
        elif self.game == 3:
            game="Partida Rápida"
        elif self.game == 4:
            game="Partida Especial Navidad"
        
        # Get lock to synchronize threads
        threadLock.acquire()
        print(self.name+", "+ str(self.start_time.time())+", "+(game))

        # Free lock to release next thread
        threadLock.release()



def make_threads():
    threads = []
    # Create 120 new threads
    for i in range(120):
        thread = myThread(i+1, "Jugador"+str(i+1), 1)
        thread.start()
        threads.append(thread)


    # Wait for all threads to complete
    for t in threads:
        t.join()
    print ("Exiting Main Thread")
    return




threadLock = threading.Lock()
make_threads()

