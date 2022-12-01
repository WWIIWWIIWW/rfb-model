Info<< "Reading field p\n" << endl;
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

#include "createPhi.H"

label pRefCell = 0;
scalar pRefValue = 0.0;
setRefCell(p, piso.dict(), pRefCell, pRefValue);
mesh.setFluxRequired(p.name());

singlePhaseTransportModel laminarTransport(U, phi);
dimensionedScalar eps("eps", dimless, laminarTransport);//read eps (porosity) value from the transportProperties directory in constant/
//dimensionedScalar beta("beta", dimless/dimLength, laminarTransport);//read forchheimer coefficient (beta) value from the transportProperties directory in constant/
//dimensionedScalar perm("perm", dimArea, laminarTransport);//read permeability value (perm) from the transportProperties directory in constant/
//dimensionedScalar nu("nu",dimViscosity,laminarTransport);// gets kinematic viscosity

autoPtr<incompressible::turbulenceModel> turbulence
(
    incompressible::turbulenceModel::New(U, phi, laminarTransport)
);

#include "createMRF.H"
#include "createFvOptions.H"

const labelList& porousCells = mesh.cellZones()[0];

volScalarField porosity
(
     IOobject
     (
	"porosity",
	runTime.timeName(),
	mesh,
        IOobject::NO_READ,
	IOobject::AUTO_WRITE // NO_WRITE
     ),
     mesh,
     dimensionedScalar("porosity",dimless,1.0)
);
 
forAll(porousCells,i)
{
	porosity[porousCells[i]] = eps.value();
}

surfaceScalarField porosityFaces = fvc::interpolate(porosity);

