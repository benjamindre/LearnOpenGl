/**
 * @file ILayer.h
 * @brief None
 * @author Benjamin Enger (benjaminenger125522@gmail.com)
 * @date 2024-08-30 17:08:04
 * @version 1.0
 */

#pragma once

class ILayer
{
public:
    virtual ~ILayer() { };

    virtual void Render(double time) = 0;
};