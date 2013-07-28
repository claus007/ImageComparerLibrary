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

#ifndef IMAGEDIFFCALCULATORJOB_H
#define IMAGEDIFFCALCULATORJOB_H

#include "threading/ImageProcessorJob.h"

class QImage;

class ImageDiffCalculatorJob : public ImageProcessorJob
{
    Q_OBJECT
public:
    explicit ImageDiffCalculatorJob();
    
    virtual void run();

    QImage *originalImage() const;
    void setOriginalImage(QImage *originalImage);

    QImage *newImage() const;
    void setNewImage(QImage *newImage);

    void returnErrorImage();
protected:
    QImage * _originalImage;
    QImage * _newImage;
signals:
    
public slots:
    
};

#endif // IMAGEDIFFCALCULATORJOB_H
