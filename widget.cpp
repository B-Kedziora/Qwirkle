#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    Game* game = new Game(this);
    connection = new Connection(&chatName, game);

    pieces_widget = findChild<QTableWidget*>("PiecesWidget");
    pieces_widget->verticalHeader()->setMaximumSectionSize(30);
    pieces_widget->verticalHeader()->setMinimumSectionSize(30);
    pieces_widget->horizontalHeader()->setMaximumSectionSize(30);
    pieces_widget->horizontalHeader()->setMinimumSectionSize(30);
    pieces_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    pieces_widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    board_widget = findChild<QTableWidget*>("BoardWidget");
    board_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    board_widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void Widget::receiveChatMessage(Message *mes)
{
    ui->MessageLog->append(QString::fromStdString(mes->getSenderName() + string(": ") + mes->getMessage()));
}

void Widget::receiveExchangeMessage(Message* message) {
    QString mes = QString::fromStdString(message->getSenderName()) + " exchanged tiles (";
    mes += QString::fromStdString(message->getMessage()) + ")";
    ui->MessageLog->append("SERVER: " + mes);
}

void Widget::receivePieces(vector<Piece> pieces) {
    int piece_index = 0;
    for (int i = 0; i < pieces_widget->rowCount(); i++) {
        for (int j = 0; j < pieces_widget->columnCount(); j++) {
            if (pieces_widget->item(i, j) != NULL) continue;
            Piece piece = pieces[piece_index];
            QIcon icon = QIcon();
            QPixmap pixmap("testicon.png");
            if (pixmap.isNull()) exit(11);
            icon.addPixmap(pixmap);
            QTableWidgetItem* tile = new QTableWidgetItem(icon, "");
            QVariant data(QString::number(piece.getColor()) + "." + QString::number(piece.getShape()) + ".");
            tile->setData(Qt::ItemDataRole::UserRole, data);
            tile->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
            pieces_widget->setItem(i, j, tile);
            piece_index++;
            if (piece_index == pieces.size()) return;
        }
    }
}

void Widget::setTurn(string message) {
    message.resize(message.length() - 1);
    string playername = message;
    if (playername == chatName) {
        ui->PlayerNameLabel->setText("Your turn!");
        ui->ExchangeButton->setEnabled(true);
        ui->PiecesWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        return;
    }
    ui->PlayerNameLabel->setText(QString::fromStdString(playername));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_SendButton_clicked()
{
    sendChatMessage();
}

void Widget::on_MessageInput_returnPressed()
{
    sendChatMessage();
}

void Widget::sendChatMessage()
{
    Message* message = new Message(Message::messageType::CHAT, ui->MessageInput->text().toStdString(), chatName);
    connection->sendMessage(message);
    ui->MessageInput->setText("");
}

void Widget::on_PiecesWidget_itemSelectionChanged()
{
    if (pieces_widget->selectedItems().size() > 0) {
        board_widget->setDragDropMode(QAbstractItemView::DragDropMode::DragDrop);
    }
}

void Widget::on_pushButton_clicked()
{
}

void Widget::on_ExchangeButton_clicked()
{
    if (pieces_widget->selectedItems().size() == 0)
        return;
    QString pieces = "";
    for (QTableWidgetItem* item : pieces_widget->selectedItems()) {
        pieces += item->data(Qt::ItemDataRole::UserRole).toString();
        delete item;
    }
    ui->ExchangeButton->setEnabled(false);
    ui->PiecesWidget->clearSelection();
    ui->PiecesWidget->setSelectionMode(QAbstractItemView::NoSelection);
    Message* message = new Message(Message::messageType::PIECE, pieces.toStdString(), chatName);
    connection->sendMessage(message);
}
