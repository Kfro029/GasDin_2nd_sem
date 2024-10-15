/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2016 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    relax equation


\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "IFstream.H"
#include "OFstream.H"
#include "IOmanip.H"
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
  argList::addOption
    (
        "T_0",
	"scalar",
        "initial temperature"
    );
  argList::addOption
    (
        "T_e",
	"scalar",
        "equilibrium temperature"
    );
  argList::addOption
    (
        "tau",
	"scalar",
        "relax time"
    );
  
#include "setRootCase.H"
#include "createTime.H"
#include "createMesh.H"

   scalar T_0 = 1.0;
   scalar T_e = 0.0;
   scalar tau = 1.0;

 if (args.readIfPresent("T_0", T_0))
    {
       Info << "T_0 = " << T_0 << endl;
    }
 if (args.readIfPresent("T_e", T_e))
    {
       Info << "T_e = " << T_e << endl;
    }
 if (args.readIfPresent("tau", tau))
    {
       Info << "tau " << tau << endl;
    }

 
 volScalarField T                         // vol - поле в ячейках Scalar - скалярное
    (
     IOobject
     (
      "T",                                // название объекта в регистре
      runTime.timeName(),                    // время
      mesh,                                  // регистр объектов
      IOobject::NO_READ,                     // опция чтения
      IOobject::AUTO_WRITE                   // опция записи
      ),
     mesh,                                   // сетка 
     dimensionedScalar("T", dimTemperature, T_0) // начальное размерное значение
     );

 volScalarField T_0_v                         // vol - поле в ячейках Scalar - скалярное
    (
     IOobject
     (
      "T_0_v",                                // название объекта в регистре
      runTime.timeName(),                    // время
      mesh,                                  // регистр объектов
      IOobject::NO_READ,                     // опция чтения
      IOobject::AUTO_WRITE                   // опция записи
      ),
     mesh,                                   // сетка 
     dimensionedScalar("T_0", dimTemperature, T_0) // начальное размерное значение
     );
 
 volScalarField T_theory                         // vol - поле в ячейках Scalar - скалярное
    (
     IOobject
     (
      "T_theory",                                // название объекта в регистре
      runTime.timeName(),                    // время
      mesh,                                  // регистр объектов
      IOobject::NO_READ,                     // опция чтения
      IOobject::AUTO_WRITE                   // опция записи
      ),
     mesh,                                   // сетка 
     dimensionedScalar("T_theory", dimTemperature, T_0) // начальное размерное значение
     );

 volScalarField rTau                         // vol - поле в ячейках Scalar - скалярное
    (
     IOobject
     (
      "rTau",                                // название объекта в регистре
      runTime.timeName(),                    // время
      mesh,                                  // регистр объектов
      IOobject::NO_READ,                     // опция чтения
      IOobject::AUTO_WRITE                   // опция записи
      ),
     mesh,                                   // сетка 
     dimensionedScalar("rTau", dimless/dimTime, 1.0/tau) // начальное размерное значение
     );

 volScalarField T_e_v                         // vol - поле в ячейках Scalar - скалярное
    (
     IOobject
     (
      "T_e",                                // название объекта в регистре
      runTime.timeName(),                    // время
      mesh,                                  // регистр объектов
      IOobject::NO_READ,                     // опция чтения
      IOobject::AUTO_WRITE                   // опция записи
      ),
     mesh,                                   // сетка 
     dimensionedScalar("T_e", dimTemperature, T_e) // начальное размерное значение
     );
 
  while(runTime.loop()) // цикл по времени
    {
      Info<< "Time = " << runTime.timeName() << nl << endl;
      T_theory = T_e_v+(T_0_v - T_e_v)*Foam::exp(-runTime.value()/tau);
      fvScalarMatrix TEqn
	(
	 fvm::ddt(T)
	 ==
	 fvc::Su(rTau*T_e_v, T)-fvm::SuSp(rTau, T)
	 );
      // first step only
      if(runTime.value() == runTime.deltaTValue())
	{
	  // A*psi = source
	  Info << "TEqn.A(): " << TEqn.A() << endl;
	  Info << "TEqn.source(): " << TEqn.source() << endl;
	  Info << "TEqn.psi(): " << TEqn.psi() << endl;
	  Info << "TEqn.D(): " << TEqn.D() << endl;
	
	  Info << "TEqn.solverDict(): " << TEqn.solverDict() << endl;
	}
      TEqn.solve();
      if(runTime.value() == runTime.deltaTValue())
	{
	  Info << "TEqn.psi(): " << TEqn.psi() << endl;
	}

      runTime.write();
    }
    return 0;
}


// ************************************************************************* //
