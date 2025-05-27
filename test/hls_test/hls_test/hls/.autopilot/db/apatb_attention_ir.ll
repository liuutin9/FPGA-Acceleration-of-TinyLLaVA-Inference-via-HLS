; ModuleID = 'C:/Users/liuut/Desktop/Project/test/hls_test/hls_test/hls/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

; Function Attrs: inaccessiblemem_or_argmemonly noinline willreturn
define void @apatb_attention_ir([3 x i32]* noalias nocapture nonnull "fpga.decayed.dim.hint"="2" %out, [3 x i32]* noalias nocapture nonnull readonly "fpga.decayed.dim.hint"="2" %q, [3 x i32]* noalias nocapture nonnull readonly "fpga.decayed.dim.hint"="2" %k, [3 x i32]* noalias nocapture nonnull readonly "fpga.decayed.dim.hint"="2" %v, i32 %d_k) local_unnamed_addr #0 {
entry:
  %0 = bitcast [3 x i32]* %out to [2 x [3 x i32]]*
  %out_copy = alloca [2 x [3 x i32]], align 512
  %1 = bitcast [3 x i32]* %q to [2 x [3 x i32]]*
  %q_copy = alloca [2 x [3 x i32]], align 512
  %2 = bitcast [3 x i32]* %k to [2 x [3 x i32]]*
  %k_copy = alloca [2 x [3 x i32]], align 512
  %3 = bitcast [3 x i32]* %v to [2 x [3 x i32]]*
  %v_copy = alloca [2 x [3 x i32]], align 512
  call fastcc void @copy_in([2 x [3 x i32]]* nonnull %0, [2 x [3 x i32]]* nonnull align 512 %out_copy, [2 x [3 x i32]]* nonnull %1, [2 x [3 x i32]]* nonnull align 512 %q_copy, [2 x [3 x i32]]* nonnull %2, [2 x [3 x i32]]* nonnull align 512 %k_copy, [2 x [3 x i32]]* nonnull %3, [2 x [3 x i32]]* nonnull align 512 %v_copy)
  call void @apatb_attention_hw([2 x [3 x i32]]* %out_copy, [2 x [3 x i32]]* %q_copy, [2 x [3 x i32]]* %k_copy, [2 x [3 x i32]]* %v_copy, i32 %d_k)
  call void @copy_back([2 x [3 x i32]]* %0, [2 x [3 x i32]]* %out_copy, [2 x [3 x i32]]* %1, [2 x [3 x i32]]* %q_copy, [2 x [3 x i32]]* %2, [2 x [3 x i32]]* %k_copy, [2 x [3 x i32]]* %3, [2 x [3 x i32]]* %v_copy)
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_in([2 x [3 x i32]]* noalias readonly, [2 x [3 x i32]]* noalias align 512, [2 x [3 x i32]]* noalias readonly, [2 x [3 x i32]]* noalias align 512, [2 x [3 x i32]]* noalias readonly, [2 x [3 x i32]]* noalias align 512, [2 x [3 x i32]]* noalias readonly, [2 x [3 x i32]]* noalias align 512) unnamed_addr #1 {
entry:
  call fastcc void @onebyonecpy_hls.p0a2a3i32([2 x [3 x i32]]* align 512 %1, [2 x [3 x i32]]* %0)
  call fastcc void @onebyonecpy_hls.p0a2a3i32([2 x [3 x i32]]* align 512 %3, [2 x [3 x i32]]* %2)
  call fastcc void @onebyonecpy_hls.p0a2a3i32([2 x [3 x i32]]* align 512 %5, [2 x [3 x i32]]* %4)
  call fastcc void @onebyonecpy_hls.p0a2a3i32([2 x [3 x i32]]* align 512 %7, [2 x [3 x i32]]* %6)
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @onebyonecpy_hls.p0a2a3i32([2 x [3 x i32]]* noalias align 512 %dst, [2 x [3 x i32]]* noalias readonly %src) unnamed_addr #2 {
entry:
  %0 = icmp eq [2 x [3 x i32]]* %dst, null
  %1 = icmp eq [2 x [3 x i32]]* %src, null
  %2 = or i1 %0, %1
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  call void @arraycpy_hls.p0a2a3i32([2 x [3 x i32]]* nonnull %dst, [2 x [3 x i32]]* nonnull %src, i64 2)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define void @arraycpy_hls.p0a2a3i32([2 x [3 x i32]]* %dst, [2 x [3 x i32]]* readonly %src, i64 %num) local_unnamed_addr #3 {
entry:
  %0 = icmp eq [2 x [3 x i32]]* %src, null
  %1 = icmp eq [2 x [3 x i32]]* %dst, null
  %2 = or i1 %1, %0
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %for.loop.cond1 = icmp sgt i64 %num, 0
  br i1 %for.loop.cond1, label %for.loop.lr.ph, label %copy.split

for.loop.lr.ph:                                   ; preds = %copy
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %for.loop.lr.ph
  %for.loop.idx2 = phi i64 [ 0, %for.loop.lr.ph ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [2 x [3 x i32]], [2 x [3 x i32]]* %dst, i64 0, i64 %for.loop.idx2
  %src.addr = getelementptr [2 x [3 x i32]], [2 x [3 x i32]]* %src, i64 0, i64 %for.loop.idx2
  call void @arraycpy_hls.p0a3i32([3 x i32]* %dst.addr, [3 x i32]* %src.addr, i64 3)
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx2, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, %num
  br i1 %exitcond, label %for.loop, label %copy.split

copy.split:                                       ; preds = %for.loop, %copy
  br label %ret

ret:                                              ; preds = %copy.split, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define void @arraycpy_hls.p0a3i32([3 x i32]* %dst, [3 x i32]* readonly %src, i64 %num) local_unnamed_addr #3 {
entry:
  %0 = icmp eq [3 x i32]* %src, null
  %1 = icmp eq [3 x i32]* %dst, null
  %2 = or i1 %1, %0
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %for.loop.cond1 = icmp sgt i64 %num, 0
  br i1 %for.loop.cond1, label %for.loop.lr.ph, label %copy.split

for.loop.lr.ph:                                   ; preds = %copy
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %for.loop.lr.ph
  %for.loop.idx2 = phi i64 [ 0, %for.loop.lr.ph ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [3 x i32], [3 x i32]* %dst, i64 0, i64 %for.loop.idx2
  %src.addr = getelementptr [3 x i32], [3 x i32]* %src, i64 0, i64 %for.loop.idx2
  %3 = load i32, i32* %src.addr, align 4
  store i32 %3, i32* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx2, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, %num
  br i1 %exitcond, label %for.loop, label %copy.split

copy.split:                                       ; preds = %for.loop, %copy
  br label %ret

ret:                                              ; preds = %copy.split, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_out([2 x [3 x i32]]* noalias, [2 x [3 x i32]]* noalias readonly align 512, [2 x [3 x i32]]* noalias, [2 x [3 x i32]]* noalias readonly align 512, [2 x [3 x i32]]* noalias, [2 x [3 x i32]]* noalias readonly align 512, [2 x [3 x i32]]* noalias, [2 x [3 x i32]]* noalias readonly align 512) unnamed_addr #4 {
entry:
  call fastcc void @onebyonecpy_hls.p0a2a3i32([2 x [3 x i32]]* %0, [2 x [3 x i32]]* align 512 %1)
  call fastcc void @onebyonecpy_hls.p0a2a3i32([2 x [3 x i32]]* %2, [2 x [3 x i32]]* align 512 %3)
  call fastcc void @onebyonecpy_hls.p0a2a3i32([2 x [3 x i32]]* %4, [2 x [3 x i32]]* align 512 %5)
  call fastcc void @onebyonecpy_hls.p0a2a3i32([2 x [3 x i32]]* %6, [2 x [3 x i32]]* align 512 %7)
  ret void
}

declare void @apatb_attention_hw([2 x [3 x i32]]*, [2 x [3 x i32]]*, [2 x [3 x i32]]*, [2 x [3 x i32]]*, i32)

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_back([2 x [3 x i32]]* noalias, [2 x [3 x i32]]* noalias readonly align 512, [2 x [3 x i32]]* noalias, [2 x [3 x i32]]* noalias readonly align 512, [2 x [3 x i32]]* noalias, [2 x [3 x i32]]* noalias readonly align 512, [2 x [3 x i32]]* noalias, [2 x [3 x i32]]* noalias readonly align 512) unnamed_addr #4 {
entry:
  call fastcc void @onebyonecpy_hls.p0a2a3i32([2 x [3 x i32]]* %0, [2 x [3 x i32]]* align 512 %1)
  ret void
}

declare void @attention_hw_stub([3 x i32]* noalias nocapture nonnull, [3 x i32]* noalias nocapture nonnull readonly, [3 x i32]* noalias nocapture nonnull readonly, [3 x i32]* noalias nocapture nonnull readonly, i32)

define void @attention_hw_stub_wrapper([2 x [3 x i32]]*, [2 x [3 x i32]]*, [2 x [3 x i32]]*, [2 x [3 x i32]]*, i32) #5 {
entry:
  call void @copy_out([2 x [3 x i32]]* null, [2 x [3 x i32]]* %0, [2 x [3 x i32]]* null, [2 x [3 x i32]]* %1, [2 x [3 x i32]]* null, [2 x [3 x i32]]* %2, [2 x [3 x i32]]* null, [2 x [3 x i32]]* %3)
  %5 = bitcast [2 x [3 x i32]]* %0 to [3 x i32]*
  %6 = bitcast [2 x [3 x i32]]* %1 to [3 x i32]*
  %7 = bitcast [2 x [3 x i32]]* %2 to [3 x i32]*
  %8 = bitcast [2 x [3 x i32]]* %3 to [3 x i32]*
  call void @attention_hw_stub([3 x i32]* %5, [3 x i32]* %6, [3 x i32]* %7, [3 x i32]* %8, i32 %4)
  call void @copy_in([2 x [3 x i32]]* null, [2 x [3 x i32]]* %0, [2 x [3 x i32]]* null, [2 x [3 x i32]]* %1, [2 x [3 x i32]]* null, [2 x [3 x i32]]* %2, [2 x [3 x i32]]* null, [2 x [3 x i32]]* %3)
  ret void
}

attributes #0 = { inaccessiblemem_or_argmemonly noinline willreturn "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #3 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="arraycpy_hls" }
attributes #4 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="copyout" }
attributes #5 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
