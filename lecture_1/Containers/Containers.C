/*---------------------------------------------------------------------------* \
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
    Containers


Description
    main containers OpenFOAM
\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "IFstream.H"
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
  //int double

  int a = 2;

  double b = 3.5;

  Info << "a = "<< a << " b = " << b << endl;

  //label scalar word

  label x = 1; // int

  scalar y = 1.5; // double

  Info << "x = " << x << " y = " << y << endl;

  word c = "CFD";
	
  Info << "c = " << c << endl;

  //List, dynamicList, dictionary

  // List<type> - статический список элементов с типом type
  List<scalar> arrayScalar(5);

  //цикл по всем элементам списка arrayScalar

  forAll(arrayScalar, i)
    {
      arrayScalar[i] = i;
    }

  Info << "arrayScalar = "<< arrayScalar << endl;

  // DynamicList<type> - динамический список элементов с типом type

  DynamicList<scalar> dynArrayScalar;

  Info << "dynArrayScalar = " << dynArrayScalar << endl;
	
  dynArrayScalar.append(1.5);
  dynArrayScalar.append(1.6);
  dynArrayScalar.append(1.7);
  dynArrayScalar.append(1.8);

  Info << "dynArrayScalar = " << dynArrayScalar << endl;

  // dictionary - словарь (ключ, значение)

  dictionary keyValue;

  keyValue.add("x", x);
  keyValue.add("y", y);
  keyValue.add("c", c);
  keyValue.add("arrayScalar", arrayScalar);
  keyValue.add("dynArrayScalar", dynArrayScalar);

  Info << keyValue << endl;

  Info << keyValue.lookupType<label>("x")<< endl;
	
  Info << keyValue["c"] << endl;
	
  // работа с векторами и тензорами (ProgrammersGuide p.22)
    
  vector U(1,2,3);
	
  tensor Sigma(1,2,3,4,5,6,7,8,9);
	
  Info << (U&U) << endl;
	
  Info << diag(Sigma) << endl;
    
  // ввод и вывод данных из файла
    
  OFstream out ("dictOut.txt");
    
  out <<"U " << U << endl;
  out <<"dynArrayScalar " << dynArrayScalar << endl;
  out <<"Sigma " << Sigma << endl;
  out <<"keyValue " << keyValue << endl;
  out <<"arrayScalar " << arrayScalar << endl;
  out <<"a " << a << endl;
  out <<"b " << b << endl;
  out <<"c " << c << endl;
    
  IFstream in ("dictIn.txt");
    
  dictionary dictIn (in);
    
  Info << dictIn << endl;
    
  List<scalar> t (dictIn.lookup("t"));
    
  Info << t << endl;
    
  //     Info << in << endl;

  return 0;
}


// ************************************************************************* //
