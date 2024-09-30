/**
 * @file IOpenGlLayer.h
 * @brief None
 * @author Benjamin Enger (benjaminenger125522@gmail.com)
 * @date 2024-08-31 11:21:06
 * @version 1.0
 */

#pragma once

class IOpenGlLayer
{
public:
    virtual ~IOpenGlLayer() {  }


    virtual void Render(double time) = 0;

};
