/*
 * texteditordialog.cpp
 * Copyright 2016, Thorbjørn Lindeijer <bjorn@lindeijer.nl>
 *
 * This file is part of Tiled.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "texteditordialog.h"
#include "ui_texteditordialog.h"

#include "session.h"
#include "utils.h"

#include <QFontDatabase>

namespace Tiled {

namespace session {
static SessionOption<bool> monospace { "textEdit.monospace", true };
} // namespace session

TextEditorDialog::TextEditorDialog(QWidget *parent)
    : QDialog(parent)
    , mUi(new Ui::TextEditorDialog)
{
    mUi->setupUi(this);
    resize(Utils::dpiScaled(size()));

    connect(mUi->monospaceFont, &QAbstractButton::toggled, this, [this] (bool checked) {
        mUi->plainTextEdit->setFont(checked ? QFontDatabase::systemFont(QFontDatabase::FixedFont)
                                            : QGuiApplication::font());
        session::monospace.set(checked);
    });

    mUi->monospaceFont->setChecked(session::monospace);

    Utils::restoreGeometry(this);
}

TextEditorDialog::~TextEditorDialog()
{
    Utils::saveGeometry(this);
    delete mUi;
}

void TextEditorDialog::setText(const QString &text)
{
    mUi->plainTextEdit->setPlainText(text);
}

QString TextEditorDialog::text() const
{
    return mUi->plainTextEdit->toPlainText();
}

void TextEditorDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        mUi->retranslateUi(this);
        break;
    default:
        break;
    }
}

} // namespace Tiled

#include "moc_texteditordialog.cpp"
