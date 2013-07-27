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

class ComparerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ComparerWidget(QWidget *parent = 0);
    ~ComparerWidget();
    
    QString originalImageFilename() const;
    void setOriginalImageFilename(const QString &originalImageFilename);

    QString newImageFilename() const;
    void setNewImageFilename(const QString &newImageFilename);

protected:
    virtual void resizeEvent(QResizeEvent *);
protected slots:
    void initialImageLoadADone(QImage * image);
    void initialImageLoadBDone(QImage * image);
    void imageResizedADone(QImage * image);
    void imageResizedBDone(QImage * image);
private:
    Ui::ComparerWidget *ui;

    QString _originalImageFilename;
    QString _newImageFilename;

    QImage _originalImage;
    QImage _newImage;

    QImage _resizedOriginalImage;
    QImage _resizedNewImage;

    QImage _resultImage;
    QImage _resizedResultImage;
};

#endif // COMPARERWIDGET_H
