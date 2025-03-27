/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "ExecuTorchValue.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Enum to define loading behavior.
 * Values can be a subset, but must numerically match exactly those defined in
 * extension/module/module.h
 */
typedef NS_ENUM(NSInteger, ExecuTorchModuleLoadMode) {
  ExecuTorchModuleLoadModeFile = 0,
  ExecuTorchModuleLoadModeMmap,
  ExecuTorchModuleLoadModeMmapUseMlock,
  ExecuTorchModuleLoadModeMmapUseMlockIgnoreErrors,
} NS_SWIFT_NAME(ModuleLoadMode);

/**
 * Represents a module that encapsulates an ExecuTorch program.
 * This class is a facade for loading programs and executing methods within them.
 */
NS_SWIFT_NAME(Module)
__attribute__((deprecated("This API is experimental.")))
@interface ExecuTorchModule : NSObject

/**
 * Initializes a module with a file path and a specified load mode.
 *
 * @param filePath A string representing the path to the ExecuTorch program file.
 * @param loadMode A value from ExecuTorchModuleLoadMode that determines the file loading behavior.
 * @return An initialized ExecuTorchModule instance.
 */
- (instancetype)initWithFilePath:(NSString *)filePath
                        loadMode:(ExecuTorchModuleLoadMode)loadMode
    NS_DESIGNATED_INITIALIZER;

/**
 * Initializes a module with a file path using the default load mode (File mode).
 *
 * @param filePath A string representing the path to the ExecuTorch program file.
 * @return An initialized ExecuTorchModule instance.
 */
- (instancetype)initWithFilePath:(NSString *)filePath;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
