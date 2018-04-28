/* OpenHoW
 * Copyright (C) 2017-2018 Mark Sowden <markelswo@gmail.com>
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
#include <PL/platform_filesystem.h>

#include "pork_engine.h"

#include "client_frontend.h"
#include "client_shader.h"

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavfilter/avfilter.h>
#include <libavdevice/avdevice.h>

const char *video_paths[]={
        /* intro */
        "/streams/sheff.bik",
        "/streams/infologo.bik",

        /* missions - move these into js script */
        "/streams/fmv_01.bik",
        "/streams/fmv_02.bik",
        "/streams/fmv_03.bik",
        "/streams/fmv_04.bik",
        "/streams/fmv_05.bik",
        "/streams/fmv_06.bik",
        "/streams/fmv_07.bik",
        "/streams/fmv_08.bik",
        "/streams/fmv_09.bik",
};

struct {
    bool is_playing;

    AVPacket        *av_packet;
    AVCodecContext  *av_codec_context;
    AVCodec         *av_codec;
    AVStream        *av_stream;
    AVFormatContext *av_format_context;
    AVFrame         *av_frame;

    unsigned int stream_index;

    struct {
        char path[PL_SYSTEM_MAX_PATH];
    } queue[4];
    unsigned int num_videos_queued; /* elements */
    unsigned int cur_video;         /* index */
} video;

void InitVideo(void) {
    memset(&video, 0, sizeof(video));

    av_register_all();
    avformat_network_init();


}

void ShutdownVideo(void) {

}

/***************************************************************/

void ClearVideoQueue(void) {
    memset(&video, 0, sizeof(video));
}

void QueueVideos(const char **videos, unsigned int num_videos) {
    if(num_videos == 0) {
        return;
    }

    ClearVideoQueue();

    for(unsigned int i = 0; i < num_videos; ++i) {
        if(plIsEmptyString(videos[i])) {
            LogWarn("encountered invalid video path at index %u, skipping!\n", i);
            continue;
        }

        size_t len = strlen(videos[i]);
        if(len >= PL_SYSTEM_MAX_PATH) {
            LogWarn("unexpected length of path - %u bytes - expect issues!\n", len);
        }

        char n_path[PL_SYSTEM_MAX_PATH];
        strncpy(n_path, videos[i], PL_SYSTEM_MAX_PATH);
        if(!plFileExists(n_path)) {
            LogWarn("failed to find video at \"%s\", skipping!\n", n_path);
            continue;
        }

        strncpy(video.queue[video.num_videos_queued].path, n_path, PL_SYSTEM_MAX_PATH);
        video.num_videos_queued++;
    }
}

void PlayVideo(const char *path) {
    ClearVideoQueue();
    QueueVideos(&path, 1);
    if(video.num_videos_queued == 0) {
        LogWarn("failed to queue video, \"%s\", aborting playback!\n", path);
        return;
    }

    video.is_playing = true;
}

void ProcessVideo(void) {
    if(!video.is_playing) {
        if(video.av_format_context != NULL) {
            avformat_close_input(&video.av_format_context);
        }

        if(video.num_videos_queued > 0 && video.cur_video != video.num_videos_queued) {
            if(avformat_open_input(&video.av_format_context, video.queue[video.cur_video].path, NULL, NULL) < 0) {
                LogWarn("failed to open video, \"%s\", for playback, skipping!\n");
                video.cur_video++;
                return;
            }
        }

        return;
    }

    do {
        if(av_read_frame(video.av_format_context, video.av_packet) < 0) {
            video.is_playing = false;
            av_packet_unref(video.av_packet);
            return;
        }

        if(video.av_packet->stream_index == video.stream_index) {

        }

        av_packet_unref(video.av_packet);
    } while(video.av_packet->stream_index != video.stream_index);
}

void DrawVideo(void) {
    static PLMesh *mesh = NULL;
    if(mesh == NULL) {
        if((mesh = plCreateMesh(PL_MESH_TRIANGLE_STRIP, PL_DRAW_STATIC, 2, 4)) == NULL) {
            Error("failed to create mesh for video renderer, aborting!\n%s\n", plGetError());
        }

        plClearMesh(mesh);

#define x 0
#define y 0
#define w 640
#define h 480

        plSetMeshVertexPosition(mesh, 0, PLVector3(x, y, 0));
        plSetMeshVertexPosition(mesh, 1, PLVector3(x, y + h, 0));
        plSetMeshVertexPosition(mesh, 2, PLVector3(x + w, y, 0));
        plSetMeshVertexPosition(mesh, 3, PLVector3(x + w, y + h, 0));

        plSetMeshUniformColour(mesh, PLColourRGB(255, 255, 255));

        plSetMeshVertexST(mesh, 0, 0, 0);
        plSetMeshVertexST(mesh, 1, 0, 1);
        plSetMeshVertexST(mesh, 2, 1, 0);
        plSetMeshVertexST(mesh, 3, 1, 1);

        plUploadMesh(mesh);
    }

    plSetShaderProgram(programs[SHADER_VIDEO]);

    /* todo pass correct texture */

    plDrawMesh(mesh);

    plSetShaderProgram(programs[SHADER_DEFAULT]);
}