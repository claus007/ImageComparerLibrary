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

#ifndef COMPARERWIDGET_H
#define COMPARERWIDGET_H

#include <QWidget>

namespace Ui {
class ComparerWidget;
}

class QResizeEvent;
class QShowEvent;

class ComparerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ComparerWidget(QWidget *parent = 0);
    ~ComparerWidget();
    
    QString originalImageFilename() const;
    QString newImageFilename() const;

    void adjustImagesToUI();
    void setFilenames(const QString &originalImageFilename, const QString &newImageFilename);
    void adjustImageBToUI();
    void adjustImageAToUI();
    void adjustImageCToUI();
protected:
    virtual void showEvent(QShowEvent *);
    virtual void resizeEvent(QResizeEvent *);
    void calculateDiff();
protected slots:
    void initialImageLoadADone(QImage * image);
    void initialImageLoadBDone(QImage * image);

    void diffDone(QImage * image);

    void imageResizedADone(QImage * image);
    void imageResizedBDone(QImage * image);
    void imageResizedCDone(QImage * image);
private:
    Ui::ComparerWidget *ui;

    QString _originalImageFilename;
    QString _newImageFilename;

    QImage _originalImage;
    QImage _newImage;

//    QImage _resizedOriginalImage;
//    QImage _resizedNewImage;

    QImage _resultImage;
    //QImage _resizedResultImage;

    int _missingImages;
};

#endif // COMPARERWIDGET_H
