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
    class Field OF example


\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
// #include "dynamicFvMesh.H"
#include "IFstream.H"
#include "OFstream.H"
#include "IOmanip.H"
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
  argList::addOption
    (
        "k",
	"scalar",
        "frequency"
    );

#include "setRootCase.H"
#include "createTime.H"
#include "createMesh.H"

   scalar k = 1; 

 if (args.readIfPresent("k", k))
    {
       Info << "k = " << k << endl;
    }

 Info << "object names: " << mesh.names() << endl;
 
 volScalarField wave                         // vol - поле в ячейках Scalar - скалярное
    (
     IOobject
     (
      "wave",                                // название объекта в регистре
      runTime.timeName(),                    // время
      mesh,                                  // регистр объектов
      IOobject::NO_READ,                     // опция чтения
      IOobject::AUTO_WRITE                   // опция записи
      ),
     mesh,                                   // сетка 
     dimensionedScalar("wave", dimless, 0.0) // начальное размерное значение
     );

 Info << "object names: " << mesh.names() << endl;
 // volScalarField& wave_ = runTime.lookupObjectRef<volScalarField>("wave");
  
  scalar L = Foam::max(mesh.C().component(0)().primitiveField()) - Foam::min(mesh.C().component(0)().primitiveField());
  Info << "L: "<< L << endl;
  
  while(runTime.loop()) // цикл по времени
    {
      forAll(wave, cellI) // цикл по центрам ячеек
	{
	  // wave.wave.primitiveField() - поле в центрах ячеек (const)
	  // wave.wave.primitiveFieldRef() - поле в центрах ячеек
	   wave.primitiveFieldRef()[cellI] = Foam::sin(runTime.value()+(mesh.C()[cellI].x()/L)*3.1415926*k);

	}
      
      // wave.boundaryField() - поле на границе (патчах)
      // wave.oldTime() - поле с предыдущего шага по времени
      // wave.prevIter() - поле с предыдущей итерации
      // wave.correctBoundaryConditions() - обновление граничных условий
      // wave.relax(alpha) - релаксация поля с коэффициентом alpha
      // wave_n+1 = (1-alpha)*wave_n + alpha*wave_n+1

      // wave.read()
      // wave.write()
      // wave.close()
      // wave.store()
      
      runTime.write();
    }
    return 0;
}


// ************************************************************************* //
