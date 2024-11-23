#include "kMeans.hpp"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
cv::Mat ipb::kMeans(const std::vector<cv::Mat>& descriptors,
                    int d,
                    int max_iter) {
    // Step 1: Flatten descriptors into a single matrix of size (total_k, n)
    int total_k = 0;
    int n = descriptors[0].cols;  // Number of features per point (assuming
                                  // all matrices have same column size)

    for (const auto& mat : descriptors) {
        total_k += mat.rows;
    }

    cv::Mat data_points(total_k, n, CV_32F);
    int row_start = 0;

    for (const auto& mat : descriptors) {
        mat.copyTo(data_points.rowRange(row_start, row_start + mat.rows));
        row_start += mat.rows;
    }

    // Step 2: Initialize centroids randomly
    cv::Mat centroids(d, n,
                      CV_32F);  // (d, n) matrix to store the centroids
    cv::RNG rng;
    for (int i = 0; i < d; ++i) {
        int rand_index = rng.uniform(
                0, total_k);  // Choose a random data point as centroid
        data_points.row(rand_index).copyTo(centroids.row(i));  // Set centroid
    }

    // Step 3: Declare a vector to store the assigned cluster for each data
    // point
    std::vector<int> labels(total_k);

    // Step 4: Main loop of k-means algorithm
    for (int iter = 0; iter < max_iter; ++iter) {
        // Step 4.1: Assign each point to the nearest centroid
        bool changed = false;

        for (int i = 0; i < total_k; ++i) {
            float min_distance = std::numeric_limits<float>::max();
            int closest_centroid = 0;

            // Compute distance to each centroid
            for (int j = 0; j < d; ++j) {
                float dist = cv::norm(data_points.row(i) -
                                      centroids.row(j));  // Euclidean distance
                if (dist < min_distance) {
                    min_distance = dist;
                    closest_centroid = j;
                }
            }

            // Assign the point to the closest centroid
            if (labels[i] != closest_centroid) {
                labels[i] = closest_centroid;
                changed = true;  // Mark that a change occurred
            }
        }

        // Step 4.2: Update centroids (compute the mean of all points in
        // each cluster)
        cv::Mat new_centroids =
                cv::Mat::zeros(d, n, CV_32F);  // New centroids matrix
        std::vector<int> cluster_sizes(
                d, 0);  // Track the number of points in each cluster

        for (int i = 0; i < total_k; ++i) {
            int cluster_id = labels[i];
            new_centroids.row(cluster_id) +=
                    data_points.row(i);  // Sum points assigned to the centroid
            cluster_sizes[cluster_id] += 1;  // Count points in each cluster
        }

        // Average the points in each cluster to update the centroids
        for (int i = 0; i < d; ++i) {
            if (cluster_sizes[i] > 0) {
                new_centroids.row(i) /=
                        cluster_sizes[i];  // Divide by the number of points
                                           // in the cluster
            }
        }

        // Step 4.3: Check for convergence (if centroids do not change
        // significantly)
        if (cv::norm(new_centroids - centroids) < 1e-4) {
            std::cout << "Converged after " << iter << " iterations."
                      << std::endl;
            break;
        }

        // Update centroids for the next iteration
        centroids = new_centroids;

        // If no change in labels, we can stop early
        if (!changed) {
            std::cout << "No change in labels. Stopping early." << std::endl;
            break;
        }
    }

    // Return the final centroids matrix (size d x n)
    return centroids;
}

// namespace ipb
