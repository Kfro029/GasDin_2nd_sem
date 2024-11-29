// Gmsh project created on Sat Nov 24 22:32:58 2024
//+
Nx1 = 80; Rx1 = 1.00;
Nx2 = 80; Rx2 = 1.00;
Ny = 80; Ry = 1.00;
Nb = 80; Rb = 0.97;
Nc = 80; Rc = 1.00;

Point(1) = {-10, -10, 0, 1.0};
Point(2) = {10, -10, 0, 1.0};
Point(3) = {40, -10, 0, 1.0};
Point(4) = {-10, 10, 0, 1.0};
Point(5) = {10, 10, 0, 1.0};
Point(6) = {40, 10, 0, 1.0};

Point(7) = {-0.9, -0.9, 0, 1.0};
Point(8) = {0.9, -0.9, 0, 1.0};
Point(9) = {-0.9, 0.9, 0, 1.0};
Point(10) = {0.9, 0.9, 0, 1.0};
Point(11) = {0, 0, 0, 1.0};

Line(1) = {1, 2}; Transfinite Line {1} = Nx1 Using Progression Rx1;
Line(2) = {2, 3}; Transfinite Line {2} = Nx2 Using Progression Rx2;
Line(3) = {4, 5}; Transfinite Line {3} = Nx1 Using Progression Rx1;
Line(4) = {5, 6}; Transfinite Line {4} = Nx2 Using Progression Rx2;
Line(5) = {1, 4}; Transfinite Line {5} = Ny Using Bump Ry;
Line(6) = {2, 5}; Transfinite Line {6} = Ny Using Bump Ry;
Line(7) = {3, 6}; Transfinite Line {7} = Ny Using Bump Ry;

Circle(8) = {7, 11, 8};  Transfinite Line {8} = Nc Using Progression Rc;
Circle(9) = {8, 11, 10};  Transfinite Line {9} = Nc Using Progression Rc;
Circle(10) = {10, 11, 9};  Transfinite Line {10} = Nc Using Progression Rc;
Circle(11) = {9, 11, 7};  Transfinite Line {11} = Nc Using Progression Rc;

Line(12) = {1, 7};  Transfinite Line {12} = Nb Using Progression Rb;
Line(13) = {2, 8};  Transfinite Line {13} = Nb Using Progression Rb;
Line(14) = {5, 10};  Transfinite Line {14} = Nb Using Progression Rb;
Line(15) = {4, 9};  Transfinite Line {15} = Nb Using Progression Rb;

Line Loop(16) = {12, 8, -13, -1};
Plane Surface(17) = {16};
Line Loop(18) = {13, 9, -14, -6};
Plane Surface(19) = {18};
Line Loop(20) = {14, 10, -15, 3};
Plane Surface(21) = {20};
Line Loop(22) = {15, 11, -12, 5};
Plane Surface(23) = {22};
Line Loop(24) = {2, 7, -4, -6};
Plane Surface(25) = {24};
Transfinite Surface {17};
Transfinite Surface {19};
Transfinite Surface {21};
Transfinite Surface {23};
Transfinite Surface {25};
Recombine Surface {17};
Recombine Surface {19};
Recombine Surface {21};
Recombine Surface {23};
Recombine Surface {25};

Extrude {0, 0, 1} {
    Surface{17, 19, 21, 23, 25};
    Layers{1};
    Recombine;
}

Physical Surface("inlet") = {112};
Physical Surface("outlet") = {126};
Physical Surface("top") = {90, 130};
Physical Surface("bottom") = {46, 122};
Physical Surface("walls") = {104, 38, 60, 82};
Physical Surface("frontAndBack") = {47, 69, 91, 113, 135, 17, 19, 21, 23, 25};
Physical Volume("internal") = {1, 2, 3, 4, 5};

