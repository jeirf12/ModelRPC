# Project using the sun RPC model on linux

## Introduction

This model is based on the calling conventions used in unix and the c programming language. It uses the xdr data serializer for data flattening by means of the virtual socket, created either in udp or tcp; and using port number 111 known as portmapper.

## User Manual

### Compilation

When downloading the project, in each server and client folder, use the following command as appropriate.

To build the client:
```
make -f makeC
```
To build the server:
```
make -f makeS
```

### Execution

First the server called `ServerBackup` is executed like this:
```
./server
```
Secondly, the server called `Administrator` is run like this:
```
./server
```
Thirdly, the server called `SongServer` is executed like this:
```
./server
```
Lastly, the `Client` named as follows is executed:
```
./client localhost
```
