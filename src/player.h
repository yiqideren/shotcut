/*
 * Copyright (c) 2012 Meltytech, LLC
 * Author: Dan Dennedy <dan@dennedy.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QIcon>
#include <QSize>
#include "mltcontroller.h"

class ScrubBar;
class QSpinBox;
class QLabel;
class TimeSpinBox;
class AudioSignal;
class QSlider;
class QAction;
class QScrollBar;
class QToolButton;
class QTabBar;
class QHBoxLayout;

class Player : public QWidget
{
    Q_OBJECT
public:
    typedef enum {
        SourceTabIndex = 0,
        ProgramTabIndex
    } TabIndex;

    explicit Player(QWidget *parent = 0);
    void connectTransport(const TransportControllable*);
    void setIn(int);
    void setOut(int);
    void setMarkers(const QList<int>&);
    QSize videoSize() const;
    int position() const {
        return m_position;
    }
    void moveVideoToScreen(int screen = -1);

signals:
    void endOfStream();
    void seeked();
    void showStatusMessage(QString);
    void audioLevels(const QVector<double>&);
    void inChanged(int);
    void outChanged(int);
    void played(double speed);
    void paused();
    void stopped();
    void seeked(int position);
    void rewound();
    void fastForwarded();
    void previousSought(int currentPosition);
    void previousSought();
    void nextSought(int currentPosition);
    void nextSought();
    void profileChanged();
    void zoomChanged(float zoom);
    void scrolledHorizontally(int x);
    void scrolledVertically(int y);

public slots:
    void play(double speed = 1.0);
    void pause();
    void stop();
    void togglePlayPaused();
    void seek(int position);
    void onProducerOpened(bool play = true);
    void postProducerOpened();
    void onMeltedUnitOpened();
    void onProducerModified();
    void onShowFrame(int position, double fps, int in, int out, int length, bool isPlaying);
    void onShowFrame(Mlt::QFrame frame);
    void onVolumeChanged(int);
    void onCaptureStateChanged(bool);
    void resetProfile();
    void rewind();
    void fastForward();
    void showPaused();
    void showPlaying();
    void switchToTab(TabIndex index);
    void enableTab(TabIndex index, bool enabled = true);
    void onTabBarClicked(int index);

protected:
    void resizeEvent(QResizeEvent* event);

private:
    void setupActions(QWidget* widget);
    void retranslateUi(QWidget* widget);
    void showAudio(Mlt::Frame* frame);
    void adjustScrollBars(float horizontal, float vertical);

    QAction *actionPlay;
    QAction *actionPause;
    QAction *actionSkipNext;
    QAction *actionSkipPrevious;
    QAction *actionRewind;
    QAction *actionFastForward;

    ScrubBar* m_scrubber;
    TimeSpinBox* m_positionSpinner;
    QLabel* m_durationLabel;
    QLabel* m_inPointLabel;
    QLabel* m_selectedLabel;
    int m_position;
    QIcon m_playIcon;
    QIcon m_pauseIcon;
    QSlider* m_volumeSlider;
    AudioSignal* m_audioSignal;
    int m_seekPosition;
    int m_previousIn;
    int m_previousOut;
    double m_savedVolume;
    int m_duration;
    bool m_isSeekable;
    int m_isMeltedPlaying;
    QScrollBar* m_horizontalScroll;
    QScrollBar* m_verticalScroll;
    QToolButton* m_zoomButton;
    QAction* m_zoomFitAction;
    QAction* m_zoomOriginalAction;
    QAction* m_zoomOutAction;
    QAction* m_zoomInAction;
    float m_zoomToggleFactor;
    QTabBar* m_tabs;
    bool m_pauseAfterPlay;
    int m_monitorScreen;
    QWidget* m_videoWidget;
    QHBoxLayout* m_videoLayout;
    QWidget* m_videoScrollWidget;
    const TransportControllable* m_currentTransport;

private slots:
    void updateSelection();
    void onInChanged(int in);
    void onOutChanged(int out);
    void on_actionSkipNext_triggered();
    void on_actionSkipPrevious_triggered();
    void onVolumeButtonToggled(bool checked);
    void onMuteButtonToggled(bool checked);
    void setZoom(float factor, const QIcon &icon);
    void zoomFit();
    void zoomOriginal();
    void zoomOut();
    void zoomIn();
    void toggleZoom(bool checked);
};

#endif // PLAYER_H
