#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "settings.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Settings"));
    setWindowIcon(QIcon(":/images/res/pepper32.png"));
    connect(this, SIGNAL(settingsChanged()),
            globalSettings, SLOT(sendChangeNotification()));
    readSettings();
}

void SettingsDialog::readSettings() {
    QString tmp;
    //bool setting;
    // ##### loader #####
    ui->preloaderCheckBox->setChecked(
                globalSettings->s.value("usePreloader", "true").toBool());
    ui->loadDelayCheckBox->setChecked(
                globalSettings->s.value("loadDelay", "false").toBool());

    // ##### cache #####
    ui->cacheSlider->setValue(
                globalSettings->s.value("cacheSize",64).toInt());
    ui->cacheLabel2->setNum(ui->cacheSlider->value());

    // ##### scaling #####
/*
    setting = globalSettings->s.value("useFastScale","false").toBool();
    if(setting==true) {
        ui->scalingQualityComboBox->setCurrentIndex(1);
    } else {
        ui->scalingQualityComboBox->setCurrentIndex(0);
    }
*/

    // ##### fit mode #####
    tmp = globalSettings->s.value("defaultFitMode","ALL").toBool();
    if(tmp == "WIDTH") {
        ui->fitModeComboBox->setCurrentIndex(1);
    }
    else if(tmp == "NORMAL") {
        ui->fitModeComboBox->setCurrentIndex(2);
    }
    else {
        ui->fitModeComboBox->setCurrentIndex(0);
    }
}

void SettingsDialog::applySettings() {
    globalSettings->s.setValue("usePreloader",
                            ui->preloaderCheckBox->isChecked());
    globalSettings->s.setValue("loadDelay",
                            ui->loadDelayCheckBox->isChecked());
    globalSettings->s.setValue("cacheSize",
                               ui->cacheSlider->value());
    globalSettings->s.setValue("defaultFitMode",
                               ui->fitModeComboBox->currentText());
    /*
    if(ui->scalingQualityComboBox->currentIndex()==1) {
        globalSettings->s.setValue("useFastScale", true);
    } else {
        globalSettings->s.setValue("useFastScale", false);
    }
    */
    emit settingsChanged();
}

void SettingsDialog::applySettingsAndClose() {
    applySettings();
    this->close();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
