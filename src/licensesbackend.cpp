#include "licensesbackend.h"

LicensesBackend::LicensesBackend(QObject *parent) : QObject(parent)
{

}

QString LicensesBackend::getQRCodeLicense()
{
    return QString("\
Copyright © 2020 Project Nayuki. (MIT License)  \
<a href='https://www.nayuki.io/page/qr-code-generator-library'>https://www.nayuki.io/page/qr-code-generator-library</a> <br/>\
Permission is hereby granted, free of charge, to any person obtaining a copy of \
this software and associated documentation files (the \"Software\"), to deal in \
the Software without restriction, including without limitation the rights to \
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of \
the Software, and to permit persons to whom the Software is furnished to do so, \
subject to the following conditions: <br/>\
<br/>\
* The above copyright notice and this permission notice shall be included in \
all copies or substantial portions of the Software. <br/>\
<br/>\
* The Software is provided \"as is\", without warranty of any kind, express or \
implied, including but not limited to the warranties of merchantability, \
fitness for a particular purpose and noninfringement. In no event shall the \
authors or copyright holders be liable for any claim, damages or other \
liability, whether in an action of contract, tort or otherwise, arising from, \
out of or in connection with the Software or the use or other dealings in the \
Software.");
}
QString LicensesBackend::getMaterialIconsLicense()
{
    return QString("\
<a href='https://material.io/resources/icons'>https://material.io/resources/icons/</a><br/> \
<a href='https://github.com/google/material-design-icons'>https://github.com/google/material-design-icons/</a><br/>\
                   ");
}
QString LicensesBackend::getSoftwareLicense()
{
    return QString("GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007");
}
