#include "mainwindow.hpp"
#include "database_manager.hpp"
#include <QCloseEvent>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>

void MainWindow::LoadItemsFromTestDirectory()
{
    DatabaseManager::LoadTestDatabase();
    DatabaseManager::Is_DatabaseChanged = true;
    UpdateItems();
}

void MainWindow::LoadItemsFromDirectory()
{
    DatabaseManager::LoadDatabase();
    UpdateItems();
}

void MainWindow::UpdateItems()
{
    ui->listWidget->clear();
    ui->textBrowser->clear();
    for(uint i = 0; auto &Disease: DatabaseManager::diseases_database) {
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(Disease.name);
        item->setData(Qt::UserRole, i++);
        //item->setIcon(QIcon(":/images/new.png"));
        //item->setToolTip("Всплывающая подсказка"); // При наведении
        //item->setStatusTip("Сообщение в строку статуса");
        //item->setWhatsThis("Подсказка \"Что это?\"");
        ui->listWidget->addItem(item);
    }
    ui->listWidget->sortItems(Qt::AscendingOrder); // Qt::AscendingOrder - сортировка A..Z
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(834, 354);
    ui->pushButton_add->setToolTip("Открывает окно добавления болезни в каталог");
    ui->pushButton_edit->setToolTip("Открывает окно редактирования болезни");
    ui->pushButton_delete->setToolTip("Удаляет выбранную болезнь");
    ui->pushButton_save->setToolTip("Сохраняет изменения каталога");
    ui->pushButton_loadTest->setToolTip("Загружает значения из тестового каталога программы");
    ui->pushButton_edit->setDisabled(1);
    ui->pushButton_delete->setDisabled(1);
    ui->pushButton_save->setDisabled(1);
    LoadItemsFromDirectory();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->pushButton_edit->setDisabled(0);
    ui->pushButton_delete->setDisabled(0);
    auto i = DatabaseManager::diseases_database[item->data(Qt::UserRole).toUInt()];
    QString text = "<b>Симптомы:</b><br>" + i.symptoms + "<br>" \
                    + "<b>Последствия и исход:</b><br>" + i.consequences + "<br>" \
                    + "<b>Рекомендуемые препараты:</b><br>" + i.medicines + "<br>" \
                    + "<b>Рекомендуемые процедуры:</b><br>" + i.procedures + "<br>";
    ui->textBrowser->setText(text);
}

void MainWindow::on_pushButton_add_clicked()
{
    QDialog dlg(this); // Инициализация диалога
    dlg.setWindowTitle("Добавить болезнь"); // Имя диалога в заголовке

    // Формы ввода текста
    QLineEdit *ledit_name = new QLineEdit(&dlg);
    QLineEdit *ledit_symptoms = new QLineEdit(&dlg);
    QLineEdit *ledit_consequences = new QLineEdit(&dlg);
    QLineEdit *ledit_recMedicines = new QLineEdit(&dlg);
    QLineEdit *ledit_recProcedures = new QLineEdit(&dlg);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(&dlg);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->button(QDialogButtonBox::Ok)->setText("Добавить");

    connect(buttonBox, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    QFormLayout *layout = new QFormLayout();
    layout->addRow("Имя болезни:", ledit_name);
    layout->addRow("Симптомы:", ledit_symptoms);
    layout->addRow("Последствия и исход:", ledit_consequences);
    layout->addRow("Рекомендуемые препараты:", ledit_recMedicines);
    layout->addRow("Рекомендуемые процедуры:", ledit_recProcedures);
    layout->addWidget(buttonBox);

    dlg.setLayout(layout);
again:
    // В случае, если пользователь нажал "Ок".
    if(dlg.exec() == QDialog::Accepted) {
        if (ledit_name->text() == ""){
            QMessageBox::warning(this, "Ошибка заполнения", "Наименование болезни пустое!");
            goto again;
        }
        struct DiseaseInfo dis;
        dis.name = ledit_name->text();
        dis.symptoms = ledit_symptoms->text();
        dis.consequences = ledit_consequences->text();
        dis.medicines = ledit_recMedicines->text();
        dis.procedures = ledit_recProcedures->text();
        DatabaseManager::diseases_database.push_back(dis);
        DatabaseManager::Is_DatabaseChanged = true;

        // Добавление нового элемента в listWidget напрямую без повторной обработки DiseasesDirectory
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(dis.name);
        item->setData(Qt::UserRole, DatabaseManager::diseases_database.size() - 1);
        ui->listWidget->addItem(item);
        ui->listWidget->sortItems(Qt::AscendingOrder);
        ui->pushButton_edit->setDisabled(1);
        ui->pushButton_delete->setDisabled(1);
        ui->pushButton_save->setDisabled(0);
    }
}

void MainWindow::on_pushButton_delete_clicked()
{
    if (ui->listWidget->count() != 0) {
        struct DiseaseInfo dis_null;
        DatabaseManager::diseases_database[ui->listWidget->currentItem()->data(Qt::UserRole).toUInt()] = dis_null;
        DatabaseManager::Is_DatabaseChanged = true;
        delete ui->listWidget->takeItem(ui->listWidget->row(ui->listWidget->currentItem()));
        ui->textBrowser->clear();
        ui->pushButton_edit->setDisabled(1);
        ui->pushButton_delete->setDisabled(1);
        ui->pushButton_save->setDisabled(0);
    } else {
        QMessageBox::warning(this, "Ошибка удаления!", "Удалять нечего!");
    }
}

void MainWindow::on_pushButton_edit_clicked()
{
    QDialog dlg(this); // Инициализация диалога
    dlg.setWindowTitle("Изменить болезнь"); // Имя диалога в заголовке

    // Формы ввода текста
    QLineEdit *ledit_name = new QLineEdit(&dlg);
    QLineEdit *ledit_symptoms = new QLineEdit(&dlg);
    QLineEdit *ledit_consequences = new QLineEdit(&dlg);
    QLineEdit *ledit_recMedicines = new QLineEdit(&dlg);
    QLineEdit *ledit_recProcedures = new QLineEdit(&dlg);

    auto s = DatabaseManager::diseases_database[ui->listWidget->currentItem()->data(Qt::UserRole).toUInt()];
    ledit_name->setText(s.name);
    ledit_symptoms->setText(s.symptoms);
    ledit_consequences->setText(s.consequences);
    ledit_recMedicines->setText(s.medicines);
    ledit_recProcedures->setText(s.procedures);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(&dlg);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    QFormLayout *layout = new QFormLayout();
    layout->addRow("Имя болезни:", ledit_name);
    layout->addRow("Симптомы:", ledit_symptoms);
    layout->addRow("Последствия и исход:", ledit_consequences);
    layout->addRow("Рекомендуемые препараты:", ledit_recMedicines);
    layout->addRow("Рекомендуемые процедуры:", ledit_recProcedures);
    layout->addWidget(buttonBox);

    dlg.setLayout(layout);
again:
    // В случае, если пользователь нажал "Ок".
    if(dlg.exec() == QDialog::Accepted) {
        if (ledit_name->text() == ""){
            QMessageBox::warning(this, "Ошибка заполнения!", "Наименование болезни пустое!");
            goto again;
        }
        struct DiseaseInfo dis;
        dis.name = ledit_name->text();
        dis.symptoms = ledit_symptoms->text();
        dis.consequences = ledit_consequences->text();
        dis.medicines = ledit_recMedicines->text();
        dis.procedures = ledit_recProcedures->text();
        DatabaseManager::diseases_database[ui->listWidget->currentItem()->data(Qt::UserRole).toUInt()] = dis;
        DatabaseManager::Is_DatabaseChanged = true;

        // Добавление нового элемента в listWidget напрямую без повторной обработки DiseasesDirectory
        ui->listWidget->currentItem()->setText(dis.name);
        ui->listWidget->sortItems(Qt::AscendingOrder);
        ui->textBrowser->clear();
        ui->pushButton_save->setDisabled(0);
    }
}

bool MainWindow::Is_SaveData()
{
    if (!DatabaseManager::Is_DatabaseChanged)
        return false;

    if (QMessageBox::question(this, "Выход", "Сохранить изменения?") == QMessageBox::Yes)
        return true;
    else return false;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (Is_SaveData())
        DatabaseManager::SaveDatabase();

    event->accept();
}

void MainWindow::on_pushButton_loadTest_clicked()
{
    if (QMessageBox::question(this, "Загрузка значений", "Вы уверены, что хотите загрузить тестовые значения?") == QMessageBox::Yes) {
        LoadItemsFromTestDirectory();
        ui->pushButton_save->setDisabled(0);
    }
}

void MainWindow::on_pushButton_save_clicked()
{
    DatabaseManager::SaveDatabase();
    DatabaseManager::Is_DatabaseChanged = false;
    ui->pushButton_save->setDisabled(1);
}

