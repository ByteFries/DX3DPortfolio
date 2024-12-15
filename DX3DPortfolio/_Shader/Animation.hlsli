#ifndef ANIMATION_FILE
#define ANIMATION_FILE
struct Frame
{
    int clipIndex;
    uint curFrame;
    uint nextFrame;
    float time;
    
    float speed;
    float3 padding;
};

struct Motion
{
    float tweenTime;
    float runningTime;
    float takeTime;
    float padding2;
    
    Frame cur, next; //블랜딩을 위해 next 추가
};

cbuffer FrameBuffer : register(b3)
{
    Motion motion;
    int hasAnimation;
}

Texture2DArray transformMap : register(t0);
Texture2DArray matrixMap : register(t1);

matrix BlendAndSkinAnimation(float4 indices, float4 weights)
{
    matrix result = 0;
    matrix curMatrix, nextMatrix;
    
    float4 c0, c1, c2, c3;
    float4 n0, n1, n2, n3;
    
    [unroll]
    for (int i = 0; i < 4; i++)
    {
        //////////// 애니메이션 로딩 ////////////
        c0 = transformMap.Load(int4(indices[i] * 4 + 0, motion.cur.curFrame, motion.cur.clipIndex, 0));
        c1 = transformMap.Load(int4(indices[i] * 4 + 1, motion.cur.curFrame, motion.cur.clipIndex, 0));
        c2 = transformMap.Load(int4(indices[i] * 4 + 2, motion.cur.curFrame, motion.cur.clipIndex, 0));
        c3 = transformMap.Load(int4(indices[i] * 4 + 3, motion.cur.curFrame, motion.cur.clipIndex, 0));

        curMatrix = matrix(c0, c1, c2, c3);
        
        n0 = transformMap.Load(int4(indices[i] * 4 + 0, motion.cur.nextFrame, motion.cur.clipIndex, 0));
        n1 = transformMap.Load(int4(indices[i] * 4 + 1, motion.cur.nextFrame, motion.cur.clipIndex, 0));
        n2 = transformMap.Load(int4(indices[i] * 4 + 2, motion.cur.nextFrame, motion.cur.clipIndex, 0));
        n3 = transformMap.Load(int4(indices[i] * 4 + 3, motion.cur.nextFrame, motion.cur.clipIndex, 0));

        matrix tmpMatrix = matrix(n0, n1, n2, n3);
        
        //////////// 다음 동작과의 선형 보간 ////////////
        curMatrix = lerp(curMatrix, tmpMatrix, motion.cur.time);
        
        //////////// 다음 프레임이 유효한 경우 블랜딩 ////////////
        [flatten]
        if (motion.next.clipIndex > -1)
        {
            c0 = transformMap.Load(int4(indices[i] * 4 + 0, motion.next.curFrame, motion.next.clipIndex, 0));
            c1 = transformMap.Load(int4(indices[i] * 4 + 1, motion.next.curFrame, motion.next.clipIndex, 0));
            c2 = transformMap.Load(int4(indices[i] * 4 + 2, motion.next.curFrame, motion.next.clipIndex, 0));
            c3 = transformMap.Load(int4(indices[i] * 4 + 3, motion.next.curFrame, motion.next.clipIndex, 0));
        
            nextMatrix = matrix(c0, c1, c2, c3);
        
            n0 = transformMap.Load(int4(indices[i] * 4 + 0, motion.next.nextFrame, motion.next.clipIndex, 0));
            n1 = transformMap.Load(int4(indices[i] * 4 + 1, motion.next.nextFrame, motion.next.clipIndex, 0));
            n2 = transformMap.Load(int4(indices[i] * 4 + 2, motion.next.nextFrame, motion.next.clipIndex, 0));
            n3 = transformMap.Load(int4(indices[i] * 4 + 3, motion.next.nextFrame, motion.next.clipIndex, 0));
        
            tmpMatrix = matrix(n0, n1, n2, n3);
        
            nextMatrix = lerp(nextMatrix, tmpMatrix, motion.next.time);
            
            curMatrix = lerp(curMatrix, nextMatrix, motion.tweenTime);
        }
        
        result += mul(weights[i], curMatrix); // 가중치를 곱해줘 스키닝 적용
    }

    return result;
}

#endif
