# Tarea 4 - Audio en C

## Construcción

Asegúrese de tener instalado el servidor Jack y los respectivos archivos de desarrollo:
```bash
sudo apt install jackd libjack-dev
```

Opcionalmente puede instalar también `QJackCtl` la cuál es una
herramienta gráfica que le permite configurar e iniciar de manera sencilla el servidor:
```bash
sudo apt install qjackctl
```

## Ejecución
### Procesamiento desde micrófono

```bash
./jack
```

### Procesamiento desde archivo

```bash
./jack -c < test.wav
```
