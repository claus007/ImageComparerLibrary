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

#include "ComparerWidget.h"
#include "ui_ComparerWidget.h"
#include "threading/ImageLoaderJob.h"
#include "threading/ImageResizeJob.h"
#include "threading/ImageDiffCalculatorJob.h"
#include <QThreadPool>

ComparerWidget::ComparerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComparerWidget),
    _missingImages(2)
{
    ui->setupUi(this);
}

ComparerWidget::~ComparerWidget()
{
    delete ui;
}

QString ComparerWidget::newImageFilename() const
{
    return _newImageFilename;
}

void ComparerWidget::adjustImageBToUI()
{
    ImageResizeJob * job=new ImageResizeJob();
    job->setImage(&_newImage);
    job->setDestSize(ui->_newImageLabel->size());

    bool bOk = connect( job, SIGNAL(done(QImage*)),this,SLOT(imageResizedBDone(QImage*)),Qt::QueuedConnection);
    Q_ASSERT(bOk);

    QThreadPool::globalInstance()->start(job);
}

void ComparerWidget::adjustImageAToUI()
{
    ImageResizeJob * job=new ImageResizeJob();
    job->setImage(&_originalImage);
    job->setDestSize(ui->_originalImageLabel->size());

    bool bOk = connect( job, SIGNAL(done(QImage*)),this,SLOT(imageResizedADone(QImage*)),Qt::QueuedConnection);
    Q_ASSERT(bOk);

    QThreadPool::globalInstance()->start(job);
}

void ComparerWidget::adjustImageCToUI()
{
    ImageResizeJob * job=new ImageResizeJob();
    job->setImage(&_resultImage);
    job->setDestSize(ui->_differenceimageLabel->size());

    bool bOk = connect( job, SIGNAL(done(QImage*)),this,SLOT(imageResizedCDone(QImage*)),Qt::QueuedConnection);
    Q_ASSERT(bOk);

    QThreadPool::globalInstance()->start(job);
}

void ComparerWidget::adjustImagesToUI()
{
    adjustImageAToUI();
    adjustImageBToUI();
    adjustImageCToUI();
}

void ComparerWidget::resizeEvent(QResizeEvent *p)
{
    QWidget::resizeEvent(p);
    // wait until images are loaded
    while ( _originalImage.isNull() || _newImage.isNull() )
    {
        QApplication::processEvents(QEventLoop::AllEvents,1);
    }

    adjustImagesToUI();

}

void ComparerWidget::calculateDiff()
{
    ImageDiffCalculatorJob * job=new ImageDiffCalculatorJob();
    job->setOriginalImage(&_originalImage);
    job->setNewImage(&_newImage);

    bool bOk = connect( job, SIGNAL(done(QImage*)),this,SLOT(diffDone(QImage*)),Qt::QueuedConnection);
    Q_ASSERT(bOk);


    QThreadPool::globalInstance()->start(job);
}

void ComparerWidget::initialImageLoadADone(QImage *image)
{
    // if image not loaded
    if ( image == NULL )
    {
        // set a red image
        _originalImage=QImage(":/images/file_broken.png");
        return;
    }

    _originalImage=*image;
    delete image;

    adjustImageAToUI();

    _missingImages--;
    if ( _missingImages == 0 )
    {
        calculateDiff();
    }
}

void ComparerWidget::initialImageLoadBDone(QImage *image)
{
    // if image not loaded
    if ( image == NULL )
    {
        // set a red image
        _originalImage=QImage(":/images/file_broken.png");
        return;
    }

    _newImage = * image;
    delete image;

    adjustImageBToUI();

    _missingImages--;
    if ( _missingImages == 0 )
    {
        calculateDiff();
    }
}

void ComparerWidget::diffDone(QImage *image)
{
    _resultImage=*image;
    delete image;

    adjustImageCToUI();
}

void ComparerWidget::imageResizedADone(QImage *image)
{
    ui->_originalImageLabel->setPixmap(QPixmap::fromImage(*image));
    delete image;
}

void ComparerWidget::imageResizedBDone(QImage *image)
{
    ui->_newImageLabel->setPixmap(QPixmap::fromImage(*image));
    delete image;
}

void ComparerWidget::imageResizedCDone(QImage *image)
{
    ui->_differenceimageLabel->setPixmap(QPixmap::fromImage(*image));
    delete image;
}

QString ComparerWidget::originalImageFilename() const
{
    return _originalImageFilename;
}

void ComparerWidget::setFilenames(
        const QString &originalImageFilename,
        const QString &newImageFilename)
{
    _originalImageFilename = originalImageFilename;

    ImageLoaderJob * job=new ImageLoaderJob();
    job->setFileName(originalImageFilename);

    bool bOk = connect( job, SIGNAL(done(QImage*)),this,SLOT(initialImageLoadADone(QImage*)),Qt::QueuedConnection);
    Q_ASSERT(bOk);

    QThreadPool::globalInstance()->start(job);

    _newImageFilename = newImageFilename;

    job=new ImageLoaderJob();
    job->setFileName(newImageFilename);

    bOk = connect( job, SIGNAL(done(QImage*)),this,SLOT(initialImageLoadBDone(QImage*)),Qt::QueuedConnection);
    Q_ASSERT(bOk);

    QThreadPool::globalInstance()->start(job);
}
