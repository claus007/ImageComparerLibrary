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

#include "ImageResizeJob.h"
#include <QImage>
#include <QPainter>

ImageResizeJob::ImageResizeJob() :
    ImageProcessorJob()
{
}

QSize ImageResizeJob::destSize() const
{
    return _destSize;
}

void ImageResizeJob::setDestSize(const QSize &destSize)
{
    _destSize = destSize;
}

const QImage *ImageResizeJob::image() const
{
    return _image;
}

void ImageResizeJob::setImage(const QImage *image)
{
    _image = image;
}

void ImageResizeJob::run()
{
    QImage * result=new QImage(_destSize,QImage::Format_ARGB32);

    //TODO transparent
    result->fill(Qt::white);

    QImage between=_image->scaled(_destSize,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    QPainter p;

    p.begin(result);

    p.drawImage(_destSize.width()/2-between.width()/2,_destSize.height()/2-between.height()/2,between);

    p.end();

    emit done(result);
}
