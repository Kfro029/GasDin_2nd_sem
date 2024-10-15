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
    Interpolation


Description
   Interpoletion class example OpenFOAM
\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "interpolateXY.H"
#include "IFstream.H"
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{ 
argList::addNote
    (
        "p, T, rho (H) Earth"
    );
 
argList::addOption
    (
        "H",
	"scalar",
        "height of Earth"
    );
 argList::noBanner();

#include "setRootCase.H" //  создается объект класса argList с именем args

 scalar H = 11111; // задаем значение высоты в метрах, на которой нужно найти термодинамические величины

 if (args.readIfPresent("H", H))
    {
       Info << "H = " << H << endl;
    }
 fileName atmospherePath = (args.path() + "/atmosphere");

 // Info << atmospherePath << endl; 

 IFstream in (atmospherePath); // создаем поток ввода из файла atmosphere

dictionary atmosphere (in); // инициализируем словарь

//Info << atmosphere << endl; // вывод словаря

// scalarField - (Field<scalar>) класс поля (наследуется от класса List) с расширенным функционалом
 
scalarField h (atmosphere.lookup("h")); // считываем массивы для h - высоты (м), T - температуры (K), p - давления (Па) и rho - плотности (кг/м^3) стандартной атмосферы Земли
scalarField T (atmosphere.lookup("T"));
scalarField p (atmosphere.lookup("p"));
scalarField rho(atmosphere.lookup("rho"));

// arguments using example
// <) FOAM/applications/utilities/surface/surfaceTransformPoints/surfaceTransformPoints.C

 
 Info << "p = " << interpolateXY<scalar>(H, h, p) << endl; // функция линейной интерполяции, вывод значения давления с высоты H
 Info << "T = " << interpolateXY<scalar>(H, h, T) << endl; // вывод значения температуры с высоты H
 Info << "rho = " <<interpolateXY<scalar>(H, h, rho) << endl; // вывод значения плотности с высоты H

 //#include "createTime.H" // создается объект класса Time с именем runTime

    return 0;
}


// ************************************************************************* //
