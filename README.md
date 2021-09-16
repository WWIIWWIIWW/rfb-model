### RFB-model

RFB-model is a suite of OpenFOAM cases and solvers
applicable to redox flow battery modelling.

- 3-D simulation of **flow in a rectangular channel**
with a porous blockage element using the Darcy-Forcheimer
model.

- Mesh of a **channel electrode**

- Tested in OpenFOAM-v2006

Test: simulate one-dimensional flow in a
rectangular channel

```
cd cases/porousBlockage_3D
./Allrun
```

Postprocess the results with paraview

```
paraview foam.foam
```

Authors
- Catalina Pino - Research Associate in Flow Battery Modelling at Imperial College London
- Felipe Huerta - 4th year PhD Student at Imperial College London
