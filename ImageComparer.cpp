/*
  
Copyright 2013 Claus Ilginnis <Claus@Ilginnis.de>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
   
     http://www.apache.org/licenses/LICENSE-2.0
     
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   
   
*/

#include "ImageComparer.h"
#include "ComparerWidget.h"
#include <QThreadPool>
#include <QThread>

void ImageComparer::init()
{
    int idealThreads=QThread::idealThreadCount();

    // if no info thik its single processor
    if ( idealThreads == -1 )
        idealThreads = 1;

    // there are also disk and network as ressources
    idealThreads+=2;

    QThreadPool *global=QThreadPool::globalInstance();

    if ( global->maxThreadCount() < idealThreads )
        global->setMaxThreadCount( idealThreads );
}

QWidget * ImageComparer::newComparer(QString orgImage, QString newImage)
{
    ComparerWidget * result= new ComparerWidget();

    result->setOriginalImageFilename(orgImage);
    result->setNewImageFilename(newImage);

    return result;
}

ImageComparer::ImageComparer()
{

}
