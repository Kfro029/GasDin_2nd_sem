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
    Time_OF


Description
   Time class example OpenFOAM
\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{ 
argList::addNote
    (
        "Time class example OpenFOAM"
    );
 
#include "setRootCase.H" //  создается объект класса argList с именем args
#include "createTime.H" // создается объект класса Time с именем runTime

//while(runTime.run()){
// runTime++
 
 while(runTime.loop()){
     // clock
     Info << endl << "clock" << endl;
     Info << "runTime.elapsedClockTime : " << runTime.elapsedClockTime() << endl;

     // dimensioned
     Info << endl << "dimensioned" << endl;
     Info << "runTime.dimensions() : "<< runTime.dimensions() << endl;
     Info << "runTime.value() : "<< runTime.value() << endl;
     dimensionedScalar x;
     dimensionedScalar newTime ("newTime", dimensionSet(0,0,1,0,0), 1.0);
     Info << "x : " << x << endl;
     Info << "newTime : " << newTime << endl;
     try {
       throw -1;
       Info << "runTime + x :" << runTime + x << endl;
     }
     catch (int a){
       Info << "OOOOOps!" << endl;
     }
     Info << "runTime + newTime :" << runTime + newTime << endl;

     // TimeState
     Info << endl << "TimeState"<< endl;
     Info << "runTime.timeIndex() : "<< runTime.timeIndex() << endl;
     Info << "runTime.deltaT() : "<< runTime.deltaT() << endl;
     Info << "runTime.deltaT0() : "<< runTime.deltaT0() << endl;
     Info << "runTime.timeOutputValue() : "<< runTime.timeOutputValue() << endl;

     // TimePaths
     Info << endl << "TimePaths"<< endl;
     Info << "runTime.times() : "<< runTime.times() << endl;
     if (runTime.value() != 0 and runTime.value() != runTime.deltaTValue())
       Info << "runTime.findClosestTime(2) : "<< runTime.findClosestTime(2) << endl;
     
     runTime.write();
     runTime.printExecutionTime(Info);
     sleep(runTime.deltaTValue());
   }

 // Time
 Info << endl << "Time" << endl;
 Info << "runTime.startTime() : "<< runTime.startTime() << endl;
 Info << "runTime.endTime() : "<< runTime.endTime() << endl;
 Info << "runTime.stopAt() : "<< runTime.stopAt() << endl;
 Info << "runTime.isAdjustTimeStep() : "<< runTime.isAdjustTimeStep() << endl;
 //Info << "runTime.libs() : "<< runTime.libs() << endl;

 // objectRegistry
 Info << endl << "objectRegistry" << endl;
 if (runTime.found("p"))
   volScalarField& p = runTime.lookupObjectRef<volScalarField>("p");
 else
   Info <<"no object with name p" <<endl;
   
 // IOobject
 
    return 0;
}


// ************************************************************************* //
