##AUTORI: Brocco Greta, Mengoli Giulia, Trevisan Giulia
## Compilazione ed esecuzione CMake

### Command Shell
1) Creare una cartella dove inserire i file di build (usare cartella build gia' presente)
2) Spostarsi nella cartella appena creata e utilizzare il comando
	
```shell
   cmake ..
```

3) Compilare con il comando
```shell
	cmake --build .
```

4) Eseguire con il comando
```shell
	./battaglia_navale
```

### Command Shell
1) Creare una cartella e copiare tutti i file .h 
   (presenti nella cartella include) e i .cpp (presenti nella cartella src)
2) Eseguire il comando per la compilazione:
```shell
   g++ Game.cpp Helper.cpp Bot.cpp Radar.cpp battaglia_navale.cpp -o battaglia_navale
 ``` 
3) Eseguire il comando per l'esecuzione:
```shell
   ./battaglia_navale
```

PROBLEMI RISCONTRATI

1. I comandi AA AA e XX XX non sono inseribili consecutivamente nello stesso turno quando il programma chiede l'inserimento
   di xyOrigin e xyTarget, altrimenti viene lanciata la classe Invalid. 
2. Siamo riuscite a realizzare parzialmente il Replay.
3. E' possibili che nelle partite computer VS computer venga randomicamente lanciata Invalid(), non siamo riuscite a sistemare 
   questo problema.
4. Nelle partite computer VS computer, con l'aumentare dei turni lo spostamento delle navi genera bug nelle griglie. 
5. Per quanto riguardo l'inserimento delle coordinate del giocatore, è possibile reinserirle solo una volta nel caso in cui la   
   prima  vengano inserite sbagliate. 

   