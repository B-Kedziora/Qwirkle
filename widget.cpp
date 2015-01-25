#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    players_turn(false),
    exchange_mode(false)
{
    ui->setupUi(this);
    Game* game = new Game(this);
    connection = new Connection(&chatName, game);

    ui->PiecesWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->PiecesWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->BoardWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->BoardWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    for (int i = 0; i < ui->PiecesWidget->rowCount(); i++) {
        for (int j = 0; j < ui->PiecesWidget->columnCount(); j++) {
            if (ui->PiecesWidget->item(i, j) != NULL) continue;
            Piece piece = pieces[piece_index];
            QIcon icon = QIcon();
            QPixmap pixmap("testicon.png");
            if (pixmap.isNull()) exit(11);
            icon.addPixmap(pixmap);
            QTableWidgetItem* tile = new QTableWidgetItem(icon, "");
            QVariant data(QString::number(piece.getColor()) + "." + QString::number(piece.getShape()) + ".");
            tile->setData(Qt::ItemDataRole::UserRole, data);
            tile->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            player_pieces.push_back(tile);
            ui->PiecesWidget->setItem(i, j, tile);
            piece_index++;
            if (piece_index == pieces.size()) return;
        }
    }
}

void Widget::setTurn(string message) {
    message.resize(message.length() - 1);
    string playername = message;
    if (playername == chatName) {
        players_turn = true;
        ui->PlayerNameLabel->setText("Your turn!");
        ui->MoveButton->setEnabled(true);
        if (exchange_mode) {
            ui->PiecesWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        } else {
            ui->PiecesWidget->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->BoardWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        }
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

void Widget::on_ExchangeRadioButton_toggled(bool checked)
{
    if (checked)  {
        exchange_mode = true;
        resetMove();
    } else {
        exchange_mode = false;
    }

    if (!players_turn)
        return;

    if (checked) {
        ui->PiecesWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    } else {
        ui->PiecesWidget->clearSelection();
        ui->PiecesWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    }
}

void Widget::resetMove() {
    for (QTableWidgetItem* piece : player_pieces) {
        if (piece->tableWidget() == ui->PiecesWidget)
            continue;

        for (int i = 0; i < ui->PiecesWidget->rowCount(); i++) {
            for (int j = 0; j < ui->PiecesWidget->columnCount(); j++) {
                if (ui->PiecesWidget->item(i, j) != NULL) continue;

                int row = piece->row();
                int column = piece->column();
                ui->PiecesWidget->setItem(i, j, ui->BoardWidget->takeItem(row, column));
                continue;
            }
            if (piece->tableWidget() == ui->PiecesWidget)
                continue;
        }
    }
}

void Widget::on_PiecesWidget_cellClicked(int row, int column)
{
    if (!players_turn || exchange_mode)
        return;
    //Move tile from BoardWidget
    if (ui->BoardWidget->selectedItems().size() > 0 && ui->PiecesWidget->item(row, column) == NULL) {
        int moved_row = ui->BoardWidget->selectedItems().first()->row();
        int moved_column = ui->BoardWidget->selectedItems().first()->column();
        ui->PiecesWidget->setItem(row, column, ui->BoardWidget->takeItem(moved_row, moved_column));
        ui->PiecesWidget->clearSelection();
        ui->BoardWidget->clearSelection();
    }
    if (ui->BoardWidget->selectedItems().size() == 0 && ui->PiecesWidget->item(row, column) != NULL)
        return;
    ui->PiecesWidget->clearSelection();
}

void Widget::on_BoardWidget_cellClicked(int row, int column)
{
    if (!players_turn || exchange_mode)
        return;

    if (ui->BoardWidget->item(row, column) == NULL) {
        if (ui->PiecesWidget->selectedItems().size() > 0) {
            // Moving tile from PiecesWidget
            int moved_row = ui->PiecesWidget->selectedItems().first()->row();
            int moved_column = ui->PiecesWidget->selectedItems().first()->column();
            ui->BoardWidget->setItem(row, column, ui->PiecesWidget->takeItem(moved_row, moved_column));
            ui->PiecesWidget->clearSelection();
            ui->BoardWidget->clearSelection();
        } else {
            ui->BoardWidget->clearSelection();
        }
        return;
    }
    if (ui->BoardWidget->item(row, column)->flags().testFlag(Qt::ItemIsSelectable)) {
        return;
    }
    ui->BoardWidget->clearSelection();
}

void Widget::on_MoveButton_clicked()
{
    // Exchanging tiles
    if (exchange_mode && ui->PiecesWidget->selectedItems().size() > 0) {
        QString pieces = "";
        for (QTableWidgetItem* item : ui->PiecesWidget->selectedItems()) {
            pieces += item->data(Qt::ItemDataRole::UserRole).toString();
            ui->PiecesWidget->takeItem(item->row(), item->column());
            delete item;
        }
        ui->MoveButton->setEnabled(false);
        ui->PiecesWidget->clearSelection();
        ui->PiecesWidget->setSelectionMode(QAbstractItemView::NoSelection);
        Message* message = new Message(Message::messageType::PIECE, pieces.toStdString(), chatName);
        connection->sendMessage(message);
        players_turn = false;
    } else if (!exchange_mode) {
        sendDropMessage();
    }
}

void Widget::sendDropMessage() {
    for (QTableWidgetItem* piece : player_pieces) {
        if (piece->tableWidget() != ui->BoardWidget)
            continue;
        int row = piece->row();
        int column = piece->column();
        Drop drop(Piece(piece->data(Qt::UserRole).toString().toStdString()), row, column);
        board.addDrop(drop);
    }
    if (!board.areDropsValid()) {
        ui->MessageLog->append("SERVER: Move not allowed");
        resetMove();
        board.deleteDrops();
    } else {
        players_turn = false;
        ui->PiecesWidget->clearSelection();
        ui->PiecesWidget->setSelectionMode(QAbstractItemView::NoSelection);
        ui->BoardWidget->clearSelection();
        ui->BoardWidget->setSelectionMode(QAbstractItemView::NoSelection);

        // Send message
        QString drop_message = "";
        for (int i = player_pieces.size() - 1; i >= 0; i--) {
            QTableWidgetItem* piece = player_pieces[i];
            if (piece->tableWidget() != ui->BoardWidget) continue;

            // TODO: Make confirmed drops not selectable.
            //piece->setFlags(piece->flags() & Qt::ItemIsSelectable);
            player_pieces.erase(player_pieces.begin() + i);

            drop_message += piece->data(Qt::ItemDataRole::UserRole).toString();
            drop_message += QString::number(piece->row()) + "." + QString::number(piece->column()) + ".";
        }
        Message* message =
                new Message(Message::messageType::MOVE, drop_message.toStdString(), chatName);
        connection->sendMessage(message);
    }
}
