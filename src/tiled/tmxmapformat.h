/*
 * tmxmapformat.h
 * Copyright 2008-2015, Thorbjørn Lindeijer <bjorn@lindeijer.nl>
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

#pragma once

#include "mapformat.h"
#include "objecttemplateformat.h"
#include "tilededitor_global.h"
#include "tilesetformat.h"

namespace Tiled {

class Tileset;
class MapObject;

/**
 * A reader and writer for Tiled's .tmx map format.
 */
class TILED_EDITOR_EXPORT TmxMapFormat : public MapFormat
{
    Q_OBJECT
    Q_INTERFACES(Tiled::MapFormat)

public:
    TmxMapFormat(QObject *parent = nullptr);

    std::unique_ptr<Map> read(const QString &fileName) override;

    bool write(const Map *map, const QString &fileName, Options options) override;

    /**
     * Converts the given map to a utf8 byte array (in .tmx format). This is
     * for storing a map in the clipboard. References to other files (like
     * tileset images) will be saved as absolute paths.
     *
     * @see fromByteArray
     */
    QByteArray toByteArray(const Map *map);

    /**
     * Reads the map given from \a data. This is for retrieving a map from the
     * clipboard. Returns null on failure.
     *
     * @see toByteArray
     */
    std::unique_ptr<Map> fromByteArray(const QByteArray &data);

    QString nameFilter() const override { return tr("Tiled map files (*.tmx *.xml)"); }

    QString shortName() const override { return QStringLiteral("tmx"); }

    bool supportsFile(const QString &fileName) const override;

    QString errorString() const override { return mError; }

private:
    QString mError;
};

/**
 * A reader and writer for Tiled's .tsx tileset format.
 */
class TILED_EDITOR_EXPORT TsxTilesetFormat : public TilesetFormat
{
    Q_OBJECT
    Q_INTERFACES(Tiled::TilesetFormat)

public:
    TsxTilesetFormat(QObject *parent = nullptr);

    SharedTileset read(const QString &fileName) override;

    bool write(const Tileset &tileset, const QString &fileName, Options options) override;

    QString nameFilter() const override { return tr("Tiled tileset files (*.tsx *.xml)"); }

    QString shortName() const override { return QStringLiteral("tsx"); }

    bool supportsFile(const QString &fileName) const override;

    QString errorString() const override { return mError; }

private:
    QString mError;
};

/**
 * A reader and writer for Tiled's .tx template format.
 */
class TILED_EDITOR_EXPORT XmlObjectTemplateFormat : public ObjectTemplateFormat
{
    Q_OBJECT
    Q_INTERFACES(Tiled::ObjectTemplateFormat)

public:
    XmlObjectTemplateFormat(QObject *parent = nullptr);

    std::unique_ptr<ObjectTemplate> read(const QString &fileName) override;

    bool write(const ObjectTemplate *objectTemplate, const QString &fileName) override;

    QString nameFilter() const override { return tr("Tiled template files (*.tx)"); }

    QString shortName() const override { return QStringLiteral("tx"); }

    bool supportsFile(const QString &fileName) const override;

    QString errorString() const override { return mError; }

private:
    QString mError;
};

} // namespace Tiled
