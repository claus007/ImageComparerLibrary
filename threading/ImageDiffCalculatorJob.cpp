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

#include "ImageDiffCalculatorJob.h"
#include <QPixmap>
#include <QPainter>
#include <QImage>
#include <QColor>
#include <QRgb>

ImageDiffCalculatorJob::ImageDiffCalculatorJob() :
    ImageProcessorJob()
{
}

void ImageDiffCalculatorJob::returnErrorImage()
{
    QImage * image=new QImage(400,300,QImage::Format_ARGB32);
    image->fill(Qt::darkRed);
    emit done(image);
}

void ImageDiffCalculatorJob::run()
{
    QImage * workspace=new QImage();
    *workspace=*_originalImage;

    QImage myNewImage=_newImage->scaled( workspace->size(),Qt::KeepAspectRatio);

    QPoint p1(workspace->size().width()/2-myNewImage.size().width()/2,
             workspace->size().height()/2-myNewImage.size().height()/2);
    QPoint p2(p1.x()+myNewImage.size().width(),
              p1.y()+myNewImage.size().height());

    // now do the diff
    for ( int x = 0 ; x < myNewImage.size().width() ; x++ )
    {
        for ( int y = 0 ; y < myNewImage.size().height() ; y++)
        {
            QPoint position(x,y);
            QRgb rgb=workspace->pixel(p1+position);
            QRgb rgb2=myNewImage.pixel(position);

            QRgb rgb3= qRgb( abs(qRed( rgb ) - qRed(rgb2 )),
                             abs(qGreen( rgb ) - qGreen(rgb2 )),
                             abs(qBlue( rgb ) - qBlue(rgb2 )) );

            workspace->setPixel(p1+position, rgb3);
        }
    }

    emit done(workspace);
}

QImage *ImageDiffCalculatorJob::newImage() const
{
    return _newImage;
}

void ImageDiffCalculatorJob::setNewImage(QImage *newImage)
{
    _newImage = newImage;
}

QImage *ImageDiffCalculatorJob::originalImage() const
{
    return _originalImage;
}

void ImageDiffCalculatorJob::setOriginalImage(QImage *originalImage)
{
    _originalImage = originalImage;
}
