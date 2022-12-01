// Solve the Momentum equation

MRF.correctBoundaryVelocity(U);

fvVectorMatrix UEqn
(
   (1.0/porosity)*fvm::ddt(U) + fvm::div((phi/pow(porosityFaces,2)), U)
  //+ MRF.DDt(U)
  + (1.0/porosity)*turbulence->divDevReff(U)
 ==
    fvOptions(U)
);

UEqn.relax();

fvOptions.constrain(UEqn);

if (piso.momentumPredictor())
{
    solve(UEqn == -fvc::grad(p));

    fvOptions.correct(U);
}
